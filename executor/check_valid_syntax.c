/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:55:25 by mher              #+#    #+#             */
/*   Updated: 2022/06/08 16:29:06 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_alone_pipe(t_cmd *cmd)
{
	if (cmd->is_pipe && cmd->argc == 0)
	{
		print_err2("syntax error near unexpected token `|'", NULL);
		g_exit_code = 258;
		return (-1);
	}
	return (0);
}

static int	check_redirection_file(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argc == 0)
		return (0);
	while (cmd->argv[i + 1])
		++i;
	if (!ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
	{
		print_err2("syntax error near unexpected token `newline'", NULL);
		g_exit_code = 258;
		return (-1);
	}
	return (0);
}

static int	check_empty_cmd(t_cmd *cmd)
{
	if (cmd->argc == 1 && cmd->argv[0] == NULL)
	{
		print_err2("", "command not found");
		g_exit_code = 127;
		return (-1);
	}
	return (0);
}

int	check_valid_syntax(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	if (check_alone_pipe(cmd_head) == -1)
		return (-1);
	while (cur)
	{
		if (check_empty_cmd(cur) == -1)
			return (-1);
		else if (check_redirection_file(cur) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
