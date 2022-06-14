/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:45:55 by mher              #+#    #+#             */
/*   Updated: 2022/06/14 14:48:52 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_need_fork(t_cmd *cmd)
{
	if (cmd->prev != NULL)
		return (1);
	if (cmd->is_pipe == true)
		return (1);
	if (cmd->infile != -2)
		return (1);
	if (cmd->outfile != -2)
		return (1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (0);
	return (1);
}

void	restore_redirection_char(t_cmd *cmd_head)
{
	t_cmd	*cur;
	int		i;
	int		j;

	cur = cmd_head;
	while (cur)
	{
		i = 0;
		while (cur->argv[i])
		{
			j = 0;
			while (cur->argv[i][j])
			{
				if (cur->argv[i][j] == -74)
					cur->argv[i][j] = '<';
				else if (cur->argv[i][j] == -76)
					cur->argv[i][j] = '>';
				++j;
			}
			++i;
		}
		cur = cur->next;
	}
}
