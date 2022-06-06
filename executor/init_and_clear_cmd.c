/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 14:46:23 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_cmd_arg(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		cmd->cmd_path = NULL;
		ft_pipe(cmd->fd);
		infile_open(cmd);
		heredoc(cmd);
		outfile_open(cmd);
		cmd->cmd_path = get_cmd_path(cmd);
		cmd = cmd->next;
	}
	return ;
}

void	clear_cmd(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	while (cur)
	{
		if (cur->is_pipe)
			ft_close(cur->fd[READ]);
		if (cur->infile != -1)
			ft_close(cur->infile);
		if (cur->outfile != -1)
			ft_close(cur->outfile);
		if (cur->cmd_path != NULL)
			free(cur->cmd_path);
		cur = cur->next;
	}
}
