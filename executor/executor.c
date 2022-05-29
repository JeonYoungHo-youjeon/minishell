/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/29 17:39:06 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"
#include "builtins/builtin.h"
#include "libft/include/libft.h"
#include <stdlib.h>

int	origin_cmd(t_cmd *cmd)
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

int	execute_needed_fork_cmd(t_cmd *cmd, t_env *env_head)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	if (ft_strcmp(cmd->argv[i], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->argv[i], "env") == 0)
		ret = ft_env(env_head);
	else if (ft_strcmp(cmd->argv[i], "echo") == 0)
		ret = ft_echo(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[i], "exit") == 0)
		ret = ft_exit(cmd->argc, cmd->argv, env_head);
	else
		origin_cmd(cmd);
	exit(EXIT_SUCCESS);
}

int	execute_unneeded_fork_cmd(t_cmd *cmd, t_env *env_head)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ret = ft_cd(cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ret = ft_export(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ret = ft_unset(cmd->argc, cmd->argv, env_head);
	return (ret);
}

int	is_need_fork(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	return (1);
}

int	redirect_input(t_cmd *cmd)
{
	int	fd;

	if (cmd->prev != 0 && cmd->prev->is_pipe)
	{
		dup2(cmd->prev->fd[READ], STDIN_FILENO);
	}
	if (ft_strcmp(cmd->argv[0], "<") == 0)
	{
		fd = open(cmd->argv[1], O_RDONLY);
		if (fd == -1)
			perror("infile open error");
		dup2(fd, STDIN_FILENO);
		cmd->argv += 2;
	}
	return (0);
}


int	redirect_output(t_cmd *cmd)
{
	int	i;
	int	fd;
	int	is_outfile;

	if (cmd->is_pipe)
		dup2(cmd->fd[WRITE], STDOUT_FILENO);
	i = 1;
	fd = -1;
	is_outfile = 0;
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0)
		{
			fd = open(cmd->argv[i + 1] , O_RDWR | O_CREAT | O_TRUNC, 0644);
			is_outfile = 1;
			close(fd);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			fd = open(cmd->argv[i + 1] , O_WRONLY | O_CREAT | O_APPEND, 0644);
			is_outfile = 1;
			close(fd);
		}
		++i;
	}
	if (is_outfile)
	{
		if (ft_strcmp(cmd->argv[cmd->argc - 2], ">") == 0)
			fd = open(cmd->argv[cmd->argc - 1] , O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(cmd->argv[cmd->argc - 2], ">>") == 0)
			fd = open(cmd->argv[cmd->argc - 1] , O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	i = 1;
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0 || ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			cmd->argv[i++] = 0;
			while (i < cmd->argc)
			{
				free(cmd->argv[i]);
				++i;
			}
		}
		else
			++i;
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	redirect_input(cmd);
	redirect_output(cmd);
	return (0);
}

int	close_unused_fd(t_cmd *cmd, pid_t pid)
{
	if (pid == 0)
	{
		if (cmd->prev != 0)
			close(cmd->prev->fd[WRITE]);
		close(cmd->fd[READ]);
	}
	else
	{
		if (cmd->prev != 0)
			close(cmd->prev->fd[READ]);
		close(cmd->fd[WRITE]);
	}
	return (0);
}

int	executor(t_cmd *cmd)
{
	t_env	env_head;
	pid_t	pid;
	//int	exit_status;
	
	init_env_list(&env_head, cmd->envp);
	while (cmd != 0)
	{
		if (is_need_fork(cmd->argv[0]) == 0)
			execute_unneeded_fork_cmd(cmd, &env_head);
		else
		{
			pipe(cmd->fd);
			pid = fork();
			if (pid == 0)
			{
				redirect(cmd);
				close_unused_fd(cmd, pid);
				execute_needed_fork_cmd(cmd, &env_head);
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
