/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:46:25 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 18:58:52 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	trim_cmd_argv(t_cmd *cmd, const char *set, int size)
{
	int	i;
	int	tmp;

	i = -1;
	while (cmd->argv[++i])
		if (!ft_strcmp(cmd->argv[i], set))
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

void	infile_open(t_cmd *cmd)
{
	int	i;

	while (1)
	{
		i = -1;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], "<"))
				break ;
		if (cmd->argv[i] == NULL)
			break ;
		cmd->infile = ft_open(cmd->argv[i + 1], O_RDONLY, 0644);
		trim_cmd_argv(cmd, "<", 2);
	}
	return ;
}

void	outfile_open(t_cmd *cmd)
{
	int	i;
	int	o_flag;

	while (1)
	{
		i = -1;
		o_flag = 0;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], ">")
					|| !ft_strcmp(cmd->argv[i], ">>"))
				break ; 
		if (cmd->argv[i] == NULL)
			break ;
		if (ft_strcmp(cmd->argv[i], ">") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_TRUNC;
			cmd->outfile = ft_open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">", 2);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
			cmd->outfile = ft_open(cmd->argv[i + 1] , o_flag, 0644);
			trim_cmd_argv(cmd, ">>", 2);
		}
	}
	return ;
}