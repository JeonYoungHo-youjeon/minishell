/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2022/06/08 16:26:22 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"

void	init_cmd_arg(t_cmd *cmd, t_env *env_head)
{
	char	*line;

	while (cmd)
	{
		if (cmd->argc == 0)
		{
			line = readline("> ");
			add_history(line);
			parse(line, cmd);
			replace(cmd, env_head);
			free(line);
		}
		cmd->infile = -1;
		cmd->outfile = -1;
		cmd->cmd_path = NULL;
		ft_pipe(cmd->fd);
		infile_open(cmd);
		heredoc(cmd);
		outfile_open(cmd);
		cmd->cmd_path = get_cmd_path(cmd, env_head);
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
