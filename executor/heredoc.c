/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/05/31 04:23:55 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft/include/libft.h"

static void	get_here_doc_input(t_cmd *cmd)
{
	char	*line;
	char	*lim;
	char	*tmp;
	char	*chunk;
	size_t	len;

	lim = cmd->argv[1];
	len = ft_strlen(lim);
	tmp = 0;
	while (1)
	{	
		line = readline("heredoc> ");
		if (ft_strcmp(line, lim) == 0)
		{
			free(line);
			break ;
		}
		chunk = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		tmp = chunk;
		chunk = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = chunk;
	}
	write(cmd->hd_fd[WRITE], chunk, ft_strlen(chunk));
	exit(EXIT_SUCCESS);
}

void	heredoc(t_cmd *cmd)
{
	pid_t	pid;

	if (ft_strcmp(cmd->argv[0], "<<"))
		return ;
	if (pipe(cmd->hd_fd) == -1)
		perror("pipe fail");
	pid = fork();
	if (pid == 0)
	{
		close(cmd->hd_fd[READ]);
		get_here_doc_input(cmd);
	}
	else
	{
		close(cmd->hd_fd[WRITE]);
		dup2(cmd->hd_fd[READ], STDIN_FILENO);
		trim_cmd_argv(cmd, cmd->argv[1], -1);
	}
}
