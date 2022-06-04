/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:22 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 17:02:33 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdbool.h>

static int	redirect_pipe_in(t_cmd *cmd)
{
	if (cmd->prev == false)
		return (0);
	return (dup2(cmd->prev->fd[READ], STDIN_FILENO));
}

static int	redirect_pipe_out(t_cmd *cmd)
{
	if (cmd->is_pipe == false) 
		return (0);
	return (dup2(cmd->fd[WRITE], STDOUT_FILENO));
}

static int	redirect_infile(t_cmd *cmd)
{
	if (cmd->infile == -1)
		return (0);
	return (dup2(cmd->infile, STDIN_FILENO));
}

static int	redirect_outfile(t_cmd *cmd)
{
	if (cmd->outfile == -1)
		return (0);
	return (dup2(cmd->outfile, STDOUT_FILENO));
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

int	redirect(t_cmd *cmd)
{
	redirect_pipe_in(cmd);
	redirect_pipe_out(cmd);
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
