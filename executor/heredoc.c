/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/02 01:59:00 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	heredoc_tmpfile(t_cmd *cmd, char *tmp_file_name)
{
	char	*line;
	char	*limiter;
	int	tmp_fd;

	limiter = cmd->argv[1];
	tmp_fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{	
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
}

int	heredoc(t_cmd *cmd)
{
	char		*tmp_file_name;
	int		fd;

	if (ft_strcmp(cmd->argv[0], "<<"))
		return (0);
	tmp_file_name = get_tmp_file_name();
	if (tmp_file_name == NULL)
		return (-1);
	heredoc_tmpfile(cmd, tmp_file_name);
	fd = open(tmp_file_name, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	trim_cmd_argv(cmd, "<<", 2);
	return (0);
}
