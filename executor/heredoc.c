/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 04:07:02 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	heredoc(t_cmd *cmd)
{
	char	*tmp_file_name;
	char	*line;
	char	*limiter;

	if (ft_strcmp(cmd->argv[0], "<<"))
		return (0);
	limiter = cmd->argv[1];
	tmp_file_name = get_tmp_file_name();
	if (tmp_file_name == NULL)
		return (-1);
	cmd->infile_fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{	
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(cmd->infile_fd, line, ft_strlen(line));
		write(cmd->infile_fd, "\n", 1);
		free(line);
	}
	close(cmd->infile_fd);
	cmd->infile_fd = open(tmp_file_name, O_RDONLY);
	free(tmp_file_name);
	trim_cmd_argv(cmd, "<<", 2);
	return (0);
}
