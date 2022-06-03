/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 04:13:13 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"
#include <stdlib.h>

static int	is_need_fork(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else
		return (1);
}

//OS 자체 builtin 명령어 수행
static int	origin_cmd(t_cmd *cmd, char *envp[])
{
	int	ret;

	ret = 0; //
	if (cmd->cmd_path == NULL)
	{
		perror("command not found");
		return (127);
	}
	ret = execve(cmd->cmd_path, cmd->argv, envp);
	if (ret == -1)
		perror("execve fail");
	return (ret);
}

static int	execute_cmd(t_cmd *cmd, t_env *env_head, char *envp[])
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return(ft_pwd());
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return((ft_cd(cmd->argv[1])));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return(ft_env(env_head));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return(ft_echo(cmd->argc, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return((ft_exit(cmd, env_head)));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return((ft_export(cmd->argc, cmd->argv, env_head)));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return((ft_unset(cmd->argc, cmd->argv, env_head)));
	else
		return(origin_cmd(cmd, envp));
}

//os_builtins()
//ft_builtins()

int	infile_open(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "<"))
		return (0);
	cmd->infile_fd = open(cmd->argv[1], O_RDONLY);
	if (cmd->infile_fd == -1)
		perror("file open error");
	trim_cmd_argv(cmd, "<", 2);
	return (0);
}

int	init_cmd_arg(t_cmd *cmd)
{
	int	ret;

	while (cmd)
	{
		cmd->infile_fd = -1;
		if (pipe(cmd->fd) == -1)
			return (-1);
		infile_open(cmd);
		ret = heredoc(cmd);
		ret = get_cmd_path(cmd);
		cmd = cmd->next;
	}
	return (0);
}

int	executor(t_cmd *cmd, t_env *env_head, char *envp[])
{
	pid_t	pid;
	int	status;

	init_cmd_arg(cmd);
	while (cmd)
	{
		if (cmd->prev == NULL && is_need_fork(cmd->argv[0]) == false)
			g_exit_code = execute_cmd(cmd, env_head, envp);
		else
		{
			pid = fork();
			if (pid == 0)
		 	{
				redirect(cmd);
				close_unused_fd(cmd, pid);
				exit(execute_cmd(cmd, env_head, envp));
			}
			else
				close_unused_fd(cmd, pid);
		}
		cmd = cmd->next;
	}
	while (wait(&status) != -1)
		g_exit_code = (((status) & 0xff00) >> 8);
		//WIFEXITED(status) 쓰면 매크로 define 이라 안되나???
	delete_tmp_file();
	//TODO: clear_pipe();
	return (0);
}
