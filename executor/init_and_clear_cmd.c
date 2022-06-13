/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2022/06/11 20:49:07 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"
#include <stdlib.h>

int	init_cmd_arg(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->is_dollar = false;
		cmd->infile = -2;
		cmd->outfile = -2;
		cmd->cmd_path = NULL;
		ft_pipe(cmd->fd);
		if (heredoc(cmd) == EXIT_FAILURE)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}

void	clear_cmd(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	while (cur)
	{
		if (cur->is_pipe)
			ft_close(cur->fd[READ]);
		if (cur->infile > 0)
			ft_close(cur->infile);
		if (cur->outfile > 0)
			ft_close(cur->outfile);
		if (cur->cmd_path != NULL)
			free(cur->cmd_path);
		cur = cur->next;
	}
}
