/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:06:24 by mher              #+#    #+#             */
/*   Updated: 2022/05/26 22:42:41 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//todo: 에러처리 해야함
void	redirect_std_fd(t_arg *arg, t_cmd *cmd)
{
	int	fd;

	if (cmd->input)
	{
		fd = open(cmd->input, O_RDONLY);
		if (fd == -1)
			perror("infile open fail");
		dup2(fd, STDIN_FILENO);
		dup2(arg->fd2[WRITE], STDOUT_FILENO);
	}
	else if (cmd->output)
	{
		fd = open(cmd->output, arg->o_flag, 0644);
		if (fd == -1)
			perror("outfile open fail");
		dup2(arg->fd1[READ], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd->pipe)
	{
		dup2(arg->fd1[READ], STDIN_FILENO);
		dup2(arg->fd2[WRITE], STDOUT_FILENO);
	}
}

//todo: 에러처리 해야함
void	close_unused_fd(t_arg *arg)
{
	int	unused_fd1;
	int	unused_fd2;

	if (arg->pid == 0)
	{
		unused_fd1 = WRITE;
		unused_fd2 = READ;
	}
	else
	{
		unused_fd1 = READ;
		unused_fd2 = WRITE;
	}
	close(arg->fd1[unused_fd1]);
	close(arg->fd2[unused_fd2]);
}
