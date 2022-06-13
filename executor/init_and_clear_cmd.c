/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2022/06/13 17:06:47 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"
#include <stdlib.h>

int	init_cmd_arg(t_cmd *cmd)
{
	t_cmd	*cur;
	
	cur = cmd;
	while (cur)
	{
		cur->is_dollar = false;
		cur->infile = -2;
		cur->outfile = -2;
		cur->cmd_path = NULL;
		if (heredoc(cur) == EXIT_FAILURE)
			return (-1);
		cur  = cur->next;
	}
	return (0);
}

void	clear_cmd(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	while (cur)
	{
		if (cur->fd[READ] != -1)
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
