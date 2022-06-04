/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 17:27:28 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"
#include <stdbool.h>
#include <stdlib.h>

static int	is_need_fork(t_cmd *cmd)
{
	if (cmd->prev != NULL)
		return (1);
	if (cmd->is_pipe == true)
		return (1);
	if (cmd->infile != -1)
		return (1);
	if (cmd->outfile != -1)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (0);
	return (1);
}

//OS 자체 builtin 명령어 수행
static int	os_builtins(t_cmd *cmd, char *envp[])
{
	if (cmd->cmd_path == NULL)
	{
		perror("command not found");
		return (127);
	}
	if (execve(cmd->cmd_path, cmd->argv, envp) == -1)
	{
		perror("execve fail");
		return (-1);
	}
	return (0);
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
		return(os_builtins(cmd, envp));
}

int	infile_open(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "<"))
		return (0);
	cmd->infile = open(cmd->argv[1], O_RDONLY);
	if (cmd->infile == -1)
		perror("file open error");
	trim_cmd_argv(cmd, "<", 2);
	return (0);
}

int	outfile_open(t_cmd *cmd)
{
	int	i;
	int	o_flag;

	while (1)
	{
		i = -1;
		o_flag = 0;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], ">")
					|| !ft_strcmp(cmd->argv[i], ">>"))
				break ; 
		if (cmd->argv[i] == NULL)
			return (0);
		if (ft_strcmp(cmd->argv[i], ">") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_TRUNC;
			cmd->outfile = open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">", 2);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
			cmd->outfile = open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">>", 2);
		}
	}
	return (0);
}

int	init_cmd_arg(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		cmd->cmd_path = NULL;
		if (pipe(cmd->fd) == -1)
			return (-1);
		if (infile_open(cmd) == -1)
			return (-1);
		if (heredoc(cmd) == -1)
			return (-1);
		if (outfile_open(cmd) == -1)
			return (-1);
		if (get_cmd_path(cmd) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}

//TODO: void 로 바꿔야 함
int	executor(t_cmd *cmd, t_env *env_head, char *envp[])
{
	pid_t	pid;
	int	status;

	init_cmd_arg(cmd);
	while (cmd)
	{
		if (is_need_fork(cmd) == false)
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
