/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/10 22:47:48 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	input_heredoc(t_cmd *cmd, int lim_i)
{
	char	*line;
	char	*limiter;

	limiter = cmd->argv[lim_i];
	while (1)
	{	
		line = readline("> ");
		if (line == NULL)
			break ;
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_write(cmd->infile, line, ft_strlen(line));
		ft_write(cmd->infile, "\n", 1);
		free(line);
	}
}

void	heredoc(t_cmd *cmd)
{
	char	*tmp_file_name;
	int		idx;

	idx = -1;
	while (cmd->argv[++idx])
		if (!ft_strcmp(cmd->argv[idx], "<<"))
			break ;
	if (cmd->argv[idx] == NULL)
		return ;
	tmp_file_name = get_tmp_file_name();
	cmd->infile = ft_open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input_heredoc(cmd, idx + 1);
	ft_close(cmd->infile);
	cmd->infile = ft_open(tmp_file_name, O_RDONLY, 0664);
	free(tmp_file_name);
	trim_cmd_argv(cmd, "<<", 2);
	return ;
}
