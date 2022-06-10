/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2022/06/10 22:23:08 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"

int	init_cmd_arg(t_cmd *cmd, t_env *env_head)
{
	while (cmd)
	{
		cmd->is_dollar = false;
		cmd->infile = -2;
		cmd->outfile = -2;
		cmd->cmd_path = NULL;
		ft_pipe(cmd->fd);
		infile_open(cmd);
		if (cmd->infile == -1)
			return (-1);
		outfile_open(cmd);
		if (cmd->outfile == -1)
			return (-1);
		heredoc(cmd);
		cmd->cmd_path = get_cmd_path(cmd, env_head);
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
		if (cur->infile != -2)
			ft_close(cur->infile);
		if (cur->outfile != -2)
			ft_close(cur->outfile);
		if (cur->cmd_path != NULL)
			free(cur->cmd_path);
		cur = cur->next;
	}
}
