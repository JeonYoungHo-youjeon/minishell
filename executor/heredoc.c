/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:54:48 by mher              #+#    #+#             */
/*   Updated: 2022/06/11 02:30:46 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	input_heredoc(t_cmd *cmd, int lim_idx)
{
	char	*line;
	char	*limiter;

	limiter = cmd->argv[lim_idx];
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

static int  wait_heredoc(pid_t pid)
{
	int		status;
	int		signo;

    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
    {
        signo = WTERMSIG(status);
        if (signo == SIGINT)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static int  do_fork_heredoc(t_cmd *cmd, int lim_idx)
{
    pid_t   pid;
    int     ret;

	set_signal(DFL, SHE);
    pid = fork();
    if (pid == 0)
    {
	    input_heredoc(cmd, lim_idx + 1);
        exit (EXIT_SUCCESS);
    }
    else
    {
       set_signal(IGN, IGN);
        ft_close(cmd->infile);
        ret = wait_heredoc(pid);
    }
    set_signal(SHE, SHE);
    return (ret);
}

int heredoc(t_cmd *cmd)
{
	char	*tmp_file_name;
	int		idx;

	idx = -1;
	while (cmd->argv[++idx])
		if (!ft_strcmp(cmd->argv[idx], "<<"))
			break ;
	if (cmd->argv[idx] == NULL)
        return (0);
	tmp_file_name = get_tmp_file_name();
	cmd->infile = ft_open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (do_fork_heredoc(cmd, idx) == EXIT_SUCCESS)
    {
        g_exit_code = EXIT_SUCCESS;
        cmd->infile = ft_open(tmp_file_name, O_RDONLY, 0664);
        free(tmp_file_name);
        trim_cmd_argv(cmd, "<<", 2);
        return (0);
    }
    else
    {
        g_exit_code = EXIT_FAILURE;
        delete_tmp_file();
        return (-1);
    }
}
