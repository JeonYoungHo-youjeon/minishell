/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:22 by mher              #+#    #+#             */
/*   Updated: 2022/06/01 23:37:24 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	redirect_pipe(t_cmd *cmd)
{
	// cmd 가 파이프로 입력을 받는 경우
	if (cmd->prev != 0 && cmd->prev->is_pipe) 
		dup2(cmd->prev->fd[READ], STDIN_FILENO);
	// cmd 가 파이프로 출력하는 경우
	if (cmd->is_pipe) 
		dup2(cmd->fd[WRITE], STDOUT_FILENO);
	return (0);
}

static int	redirect_infile(t_cmd *cmd)
{
	int	fd;

	if (ft_strcmp(cmd->argv[0], "<"))
		return (0);
	fd = open(cmd->argv[1], O_RDONLY);
	if (fd == -1)
		perror("file open error");
	dup2(fd, STDIN_FILENO);
	trim_cmd_argv(cmd, "<", 2);
	return (0);
}

void	trim_cmd_argv(t_cmd *cmd, const char *set, int size)
{
	int	i;
	int	tmp;

	i = -1;
	while (cmd->argv[++i])
		if (ft_strcmp(cmd->argv[i], set) == 0)
			break ; 
	if (cmd->argv[i] == NULL)
		return ;
	tmp = i;
	cmd->argc -= size;
	while (size--)
	{
		while (cmd->argv[i])
		{
			cmd->argv[i] = cmd->argv[i + 1];
			++i;
		}
		free(cmd->argv[i]);
		i = tmp;
	}
}

static int	redirect_outfile(t_cmd *cmd)
{
	int	i;
	int	fd;
	int	o_flag;

	while (1)
	{
		i = -1;
		fd = -1;
		o_flag = 0;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
				break ; 
		if (cmd->argv[i] == NULL)
			return (0);
		if (ft_strcmp(cmd->argv[i], ">") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_TRUNC;
			fd = open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">", 2);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">>", 2);
		}
		if (fd != -1)
			dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	redirect_pipe(cmd);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	return (0);
}

int	close_unused_fd(t_cmd *cmd, pid_t pid)
{
	if (pid == 0)
		close(cmd->fd[READ]);
	else
		close(cmd->fd[WRITE]);
	return (0);
}
