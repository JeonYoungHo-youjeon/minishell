/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 01:17:46 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

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
	return (1);
}

//OS 자체 builtin 명령어 수행
static int	origin_cmd(t_cmd *cmd, char *envp[])
{
	int	i;
	int	ret;
	char	**path;
	char	*cmd_path;

	ret = 0; //
	path = ft_split(getenv("PATH"), ':');
//	if (path);
//		return (
	cmd_path = get_cmd_path(cmd->argv[0], path);
	if (cmd_path == NULL)
	{
		perror("command not found");
		return (127);
	}
	ret = execve(cmd_path, cmd->argv, envp);
	if (ret == -1)
		perror("execve fail");
	i = 0;
	while(path[i])
		free(path[i++]);
	free(path);
	free(cmd_path);
	return (ret);
}

static int	execute_cmd(t_cmd *cmd, t_env *env_head, char *envp[])
{
	int	exit_code;

	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		exit_code = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		exit_code = (ft_cd(cmd->argv[1]));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		exit_code = ft_env(env_head);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		exit_code = ft_echo(cmd->argc, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exit_code = (ft_exit(cmd, env_head));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		exit_code = (ft_export(cmd->argc, cmd->argv, env_head));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		exit_code = (ft_unset(cmd->argc, cmd->argv, env_head));
	else
		exit_code = origin_cmd(cmd, envp);
	return (exit_code);
}

int	executor(t_cmd *cmd, t_env *env_head, char *envp[])
{
	pid_t	pid;
	int	status;
	
	while (cmd != 0)
	{
		if (cmd->prev == NULL && is_need_fork(cmd->argv[0]) == 0)
			execute_cmd(cmd, env_head, envp);
		else
		{
			if (pipe(cmd->fd) == -1)
				return (-1);
			heredoc_input(cmd);
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
		//(((status) & 0xff00) >> 8) 대신 WIFEXITED(status) 로 쓰면
		//매크로 define 이라 쓰면 안되나???
	delete_tmp_file();
	return (0);
}
