/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:06:24 by mher              #+#    #+#             */
/*   Updated: 2022/05/28 17:16:26 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//todo: 에러처리 해야함
int	redirect_infile(t_arg *arg, char *infile, int o_flag)
{
	int	fd;

	fd = open(infile, o_flag);
	if (fd == -1)
		perror("infile open fail");
	dup2(fd, STDIN_FILENO);
	dup2(arg->fd2[WRITE], STDOUT_FILENO);
	return (0);
}

//todo: 에러처리 해야함
int	redirect_outfile(t_arg *arg, char *outfile, int o_flag)
{
	int	fd;

	fd = open(outfile, o_flag, 0644);
	if (fd == -1)
		perror("outfile open fail");
	dup2(arg->fd1[READ], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	return (0);
}

//todo: 에러처리 해야함
//void	redirect_std_fd(t_arg *arg)
//{
//	int	fd;
//
//	if (arg->infile)
//	{
//		fd = open(arg->infile, O_RDONLY);
//		if (fd == -1)
//			perror("infile open fail");
//		dup2(fd, STDIN_FILENO);
//		dup2(arg->fd2[WRITE], STDOUT_FILENO);
//	}
//	else if (arg->outfile)
//	{
//		fd = open(arg->outfile, arg->o_flag, 0644);
//		if (fd == -1)
//			perror("outfile open fail");
//		dup2(arg->fd1[READ], STDIN_FILENO);
//		dup2(fd, STDOUT_FILENO);
//	}
//	else if (arg->pipe)
//	{
//		dup2(arg->fd1[READ], STDIN_FILENO);
//		dup2(arg->fd2[WRITE], STDOUT_FILENO);
//	}
//}

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
