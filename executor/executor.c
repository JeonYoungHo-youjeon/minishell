/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/30 19:52:43 by mher             ###   ########.fr       */
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
	return (1);
}

static int	origin_cmd(t_cmd *cmd)
{
	int	i;
	int	ret;
	char	**path;
	char	*cmd_path;

	path = ft_split(getenv("PATH"), ':');
//	if (path);
//		return ()
	cmd_path = get_path_cmd(path, cmd->argv[0]);
	//if (arg->cmd_path == NULL)
		//exit_with_perror("command not found", 127);
	ret = execve(cmd_path, cmd->argv, cmd->envp);
	//if (ret == -1)
		//exit_with_perror("execve fail", EXIT_FAILURE);
	i = 0;
	while(path[i])
		free(path[i++]);
	free(path);
	free(cmd_path);
	return (ret);
}

static int	execute_do_fork_cmd(t_cmd *cmd, t_env *env_head)
{
	int	ret;

	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ret = ft_env(env_head);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ret = ft_echo(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ret = ft_exit(cmd->argc, cmd->argv, env_head);
	else
		ret = origin_cmd(cmd);
	//if (ret == -1)
	//	perror();
	exit(EXIT_SUCCESS);
}

static int	execute_not_fork_cmd(t_cmd *cmd, t_env *env_head)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argv[1]));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argc, cmd->argv, env_head));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argc, cmd->argv, env_head));
	else
		return (-1);
}

int	executor(t_cmd *cmd, t_env *env_head)
{
	pid_t	pid;
	//int	exit_status;
	
	while (cmd != 0)
	{
		if (is_need_fork(cmd->argv[0]) == 0)
			execute_not_fork_cmd(cmd, env_head);
		else
		{
			pipe(cmd->fd);
			pid = fork();
			if (pid == 0)
			{
				redirect(cmd);
				close_unused_fd(cmd, pid);
				execute_do_fork_cmd(cmd, env_head);
			}
			else
				close_unused_fd(cmd, pid);
		}
		cmd = cmd->next;	
	}
	while (wait(0) != -1)
		;
	return (0);
}
