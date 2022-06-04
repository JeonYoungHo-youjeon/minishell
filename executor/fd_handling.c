/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:22 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 01:11:22 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdbool.h>

static void	redirect_pipe_in(t_cmd *cmd)
{
	if (cmd->prev == false)
		return ;
	return (ft_dup2(cmd->prev->fd[READ], STDIN_FILENO));
}

static void	redirect_pipe_out(t_cmd *cmd)
{
	if (cmd->is_pipe == false) 
		return ;
	return (ft_dup2(cmd->fd[WRITE], STDOUT_FILENO));
}

static void	redirect_infile(t_cmd *cmd)
{
	if (cmd->infile == -1)
		return ;
	return (ft_dup2(cmd->infile, STDIN_FILENO));
}

static void	redirect_outfile(t_cmd *cmd)
{
	if (cmd->outfile == -1)
		return ;
	return (ft_dup2(cmd->outfile, STDOUT_FILENO));
}

void	redirect(t_cmd *cmd)
{
	redirect_pipe_in(cmd);
	redirect_pipe_out(cmd);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	return ;
}

void	close_unused_fd(t_cmd *cmd, pid_t pid)
{
	if (pid == 0)
		ft_close(cmd->fd[READ]);
	else
		ft_close(cmd->fd[WRITE]);
	return ;
}
