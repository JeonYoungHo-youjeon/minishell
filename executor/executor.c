/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 20:56:09 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

static int	is_need_fork(t_cmd *cmd)
{
	if (cmd->prev != NULL)
		return (1);
	else if (cmd->is_pipe == true)
		return (1);
	else if (cmd->infile != -1)
		return (1);
	else if (cmd->outfile != -1)
		return (1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (0);
	return (1);
}

//OS 자체 builtin 명령어 수행
static int	os_builtins(t_cmd *cmd, char *envp[])
{
	if (cmd->cmd_path == NULL)
	{
		print_err3(cmd->argv[0], NULL,"command not found");
		return (127);
	}
	ft_execve(cmd->cmd_path, cmd->argv, envp);
	return (EXIT_FAILURE);
}

static int	execute_cmd(t_cmd *cmd, t_env *env_head, char *envp[])
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return(ft_echo(cmd->argc, cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return(ft_cd(cmd->argv[1], env_head));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return(ft_pwd());
	if (!ft_strcmp(cmd->argv[0], "export"))
		return(ft_export(cmd->argc, cmd->argv, env_head));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return(ft_unset(cmd->argc, cmd->argv, env_head));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return(ft_env(env_head));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return(ft_exit(cmd));
	return(os_builtins(cmd, envp));
}

static void	init_cmd_arg(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		cmd->cmd_path = NULL;
		ft_pipe(cmd->fd);
		infile_open(cmd);
		heredoc(cmd);
		outfile_open(cmd);
		cmd->cmd_path = get_cmd_path(cmd);
		cmd = cmd->next;
	}
	return ;
}

static void	do_fork_cmd(t_cmd *cmd, t_env *env_head, char *envp[])
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		redirect(cmd);
		close_unused_fd(cmd, pid);
		exit(execute_cmd(cmd, env_head, envp));
	}
	else
		close_unused_fd(cmd, pid);
	return ;
}

static void	clear_cmd(t_cmd *cmd_head)
{
	t_cmd	*cur;

	cur = cmd_head;
	while (cur)
	{
		if (cur->is_pipe)
			ft_close(cur->fd[READ]);
		if (cur->infile != -1)
			ft_close(cur->infile);
		if (cur->outfile != -1)
			ft_close(cur->outfile);
		if (cur->cmd_path != NULL)
			free(cur->cmd_path);
		cur = cur->next;
	}
}

void	executor(t_cmd *cmd_head, t_env *env_head, char *envp[])
{
	int	status;
	t_cmd	*cur;

	cur = cmd_head;
	init_cmd_arg(cur);
	while (cur)
	{
		if (is_need_fork(cur) == true)
			do_fork_cmd(cur, env_head, envp);
		else
			g_exit_code = execute_cmd(cur, env_head, envp);
		cur = cur->next;
	}
	while (wait(&status) != -1)
		g_exit_code = (((status) & 0xff00) >> 8);
		//WIFEXITED(status) 쓰면 매크로 define 이라 안되나???
	delete_tmp_file();
	clear_cmd(cmd_head);
	return ;
}
