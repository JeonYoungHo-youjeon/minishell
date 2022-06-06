/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 00:04:48 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	heredoc(t_cmd *cmd)
{
	char	*tmp_file_name;
	char	*line;
	char	*limiter;

	if (ft_strcmp(cmd->argv[0], "<<"))
		return ;
	limiter = cmd->argv[1];
	tmp_file_name = get_tmp_file_name();
	cmd->infile = ft_open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{	
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_write(cmd->infile, line, ft_strlen(line));
		ft_write(cmd->infile, "\n", 1);
		free(line);
	}
	ft_close(cmd->infile);
	cmd->infile = ft_open(tmp_file_name, O_RDONLY, 0664);
	free(tmp_file_name);
	trim_cmd_argv(cmd, "<<", 2);
}
