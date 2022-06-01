/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/01 20:13:22 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	get_here_doc_input(t_cmd *cmd)
{
	char	*line;
	char	*lim;
	size_t	len;
	int	tmp_fd;

	lim = cmd->argv[1];
	len = ft_strlen(lim);
	tmp_fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{	
		line = readline("> ");
		if (ft_strcmp(line, lim) == 0)
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
	int	tmp_fd;

	if (ft_strcmp(cmd->argv[0], "<<"))
		return (0);
	get_here_doc_input(cmd);
	tmp_fd = open("tmp_file", O_RDONLY);
	dup2(tmp_fd, STDIN_FILENO);
	trim_cmd_argv(cmd, cmd->argv[1], -1);
	return (0);
}
