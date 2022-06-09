/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:55:25 by mher              #+#    #+#             */
/*   Updated: 2022/06/09 19:10:36 by youjeon          ###   ########.fr       */
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
	while (i < cmd->argc)
	{
		if (!ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
		{
			if (cmd->argv[i + 1] == NULL)
			{
				print_err2("syntax error near unexpected token `newline'", NULL);
				g_exit_code = 258;
				return (-1);
			}
			else if (ft_strlen(cmd->argv[i + 1]) == 0)
			{
				print_err2("syntax error near unexpected token `newline'", NULL);
				g_exit_code = 258;
				return (-1);
			}
		}
		++i;
	}
	return (0);
}

static int	check_empty_cmd(t_cmd *cmd)
{
	if (cmd->is_dollar == false &&  cmd->argc == 1 && !ft_strcmp(cmd->argv[0], ""))
	{
		print_err2("", "command not found");
		g_exit_code = 127;
		return (-1);
	}
	return (0);
}

static int	check_dollar(t_cmd *cmd)
{
	if (cmd->is_dollar == true && cmd->argc == 1 && !ft_strcmp(cmd->argv[0], ""))
		return (-1);
	return (0);
}

int	check_valid_syntax(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	if (cur->argc == 0)
		return (-1);
	if (check_dollar(cmd_head) == -1)
		return (-1);
	if (check_alone_pipe(cmd_head) == -1)
		return (-1);
	while (cur)
	{
		if (cur->argc == 0)
		{
			cur = cur->next;
			continue ;
		}
		if (check_empty_cmd(cur) == -1)
			return (-1);
		else if (check_redirection_file(cur) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
