/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:46:25 by mher              #+#    #+#             */
/*   Updated: 2022/06/13 13:48:26 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	trim_cmd_argv(t_cmd *cmd, const char *set, int size)
{
	int	i;
	int	tmp;
	int	tmp_argc;

	i = -1;
	tmp_argc = cmd->argc;
	while (++i < cmd->argc)
		if (!ft_strcmp(cmd->argv[i], set))
			break ;
	if (i == cmd->argc)
		return ;
	tmp = i;
	cmd->argc -= size;
	while (size--)
	{
		free(cmd->argv[i]);
		while (i < tmp_argc)
		{
			cmd->argv[i] = cmd->argv[i + 1];
			++i;
		}
		i = tmp;
	}
}

static void	infile_open(t_cmd *cmd)
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
		if (cmd->infile > 0)
			close(cmd->infile);
		cmd->infile = open(cmd->argv[i + 1], O_RDONLY, 0644);
		if (cmd->infile == -1)
			print_err3(cmd->argv[i + 1], NULL, "No such file or directory");
		trim_cmd_argv(cmd, "<", 2);
	}
	return ;
}

static void	outfile_open_trim(t_cmd *cmd, const char *set, int i, int o_flag)
{
	cmd->outfile = ft_open(cmd->argv[i + 1], o_flag, 0644);
	trim_cmd_argv(cmd, set, 2);
}

static void	outfile_open(t_cmd *cmd)
{
	int	i;
	int	o_flag;

	while (1)
	{
		i = -1;
		o_flag = 0;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
				break ;
		if (cmd->argv[i] == NULL)
			break ;
		if (cmd->outfile > 0)
			close(cmd->outfile);
		if (ft_strcmp(cmd->argv[i], ">") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_TRUNC;
			outfile_open_trim(cmd, ">", i, o_flag);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
			outfile_open_trim(cmd, ">>", i, o_flag);
		}
	}
}

int	io_file_open(t_cmd *cmd, t_env *env_head)
{
	infile_open(cmd);
	if (cmd->infile == -1)
	{
		g_exit_code = EXIT_FAILURE;
		return (-1);
	}
	outfile_open(cmd);
	cmd->cmd_path = get_cmd_path(cmd, env_head);
	return (0);
}
