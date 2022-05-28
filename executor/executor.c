/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/28 17:32:35 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	execute_cmd(t_arg *arg, t_cmd *cmd)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (arg->infile || arg->heredoc)
		i = 2;
	if (ft_strcmp(cmd->argv[i], "cd") == 0)
		ret = ft_cd(cmd->argv[i + 1]);
	else if (ft_strcmp(cmd->argv[i], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->argv[i], "env") == 0)
		ret = ft_env(arg->env_head);
	else if (ft_strcmp(cmd->argv[i], "echo") == 0)
		ret = ft_echo(cmd->argc, cmd->argv, arg->env_head);
	else if (ft_strcmp(cmd->argv[i], "export") == 0)
		ret = ft_export(cmd->argc, cmd->argv, arg->env_head);
	else if (ft_strcmp(cmd->argv[i], "unset") == 0)
		ret = ft_unset(cmd->argc, cmd->argv, arg->env_head);
	else if (ft_strcmp(cmd->argv[i], "exit") == 0)
		ret = ft_exit(cmd->argc, cmd->argv, arg->env_head);
	//else //todo: linux builtin 함수 실행
	//	builtin();
	return (ret);
}

int	is_need_fork(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	return (1);
}

void	updata_arg(t_arg *arg, t_cmd *cmd)
{
	int	i;

	if (ft_strcmp(cmd->argv[0], "<") == 0)
		arg->infile = cmd->argv[1];
	else if (ft_strcmp(cmd->argv[0], "<<") == 0)
		arg->heredoc = 1;
	i = 1;
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0)
			arg->redirection = 1;
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
			arg->redirection = 1;
		if (arg->redirection == 1)
			break ;
		++i;
	}
}

int	heredoc(t_arg *arg, t_cmd *cmd)
{
	(void)arg;
	(void)cmd;
	return (0);
}

int	infile(t_arg *arg, t_cmd *cmd)
{
	(void)arg;
	(void)cmd;
	int	o_flag;

	o_flag = O_RDONLY;
	redirect_infile(arg, arg->infile, o_flag);
	return (0);
}

//ls -l | cat > a > b
//cat > a > b
int	redirection_process(t_arg *arg, t_cmd *cmd)
{
	int	i;
	int	o_flag;

	i = 1;
	if (arg->infile)
		infile(arg, cmd);
	else if (arg->heredoc)
		heredoc(arg, cmd);
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0)
			break;
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
			break;
		++i;
	}
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0)
			o_flag = O_RDWR | O_CREAT | O_TRUNC;
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
		redirect_outfile(arg, cmd->argv[i + 1], o_flag);
		arg->pid = fork();
		if (arg->pid == -1) //todo: perror()
			return (-1);
		if (arg->pid == 0)
			execute_cmd(arg, cmd);
		i += 2;
	}
	return (0);
}


int	pipe_process(t_arg *arg, t_cmd *cmd)
{
	(void)arg;
	(void)cmd;
	if (arg->infile)
		infile(arg, cmd);
	else if (arg->heredoc)
		heredoc(arg, cmd);
	return (0);
}

int	nomal_process(t_arg *arg, t_cmd *cmd)
{
	if (arg->infile)
		infile(arg, cmd);
	else if (arg->heredoc)
		heredoc(arg, cmd);
	execute_cmd(arg, cmd);
	return (0);
}


int	init_arg(t_arg	*arg, t_cmd *cmd)
{
	arg->envp = cmd->envp;
	arg->infile = 0;
	arg->append = 0;
	arg->heredoc = 0;
	arg->pipe = 0;
	arg->redirection = 0;
	arg->fd1[READ] = STDIN_FILENO;
	arg->fd2[WRITE] = STDOUT_FILENO;
	arg->o_flag = 0;
	arg->pid = 0;
	init_env_list(arg->env_head, arg->envp);
	return (0);
}

int	executor(t_cmd *cmd)
{
	t_arg	arg;
	//int	exit_status;
	
	int	tmp;
	tmp = 0;

	init_arg(&arg, cmd);
	while (cmd != 0)
	{
		updata_arg(&arg, cmd);
		if (is_need_fork(cmd->argv[0]) == 0)
			execute_cmd(&arg, cmd);
		else
		{
			if (arg.redirection)
			{
				printf("----------1\n");
				redirection_process(&arg, cmd);
			}
			else if (arg.pipe)
			{
				printf("----------2\n");
				pipe_process(&arg, cmd);
			}
			else
			{
				printf("----------3\n");
				nomal_process(&arg, cmd);
			}
		}
		cmd = cmd->next;	
	}
	return (0);
}
