/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/28 15:24:39 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	execute_cmd(t_cmd *cmd, t_env *env_head)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ret = ft_cd(cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0) //fork
		ret = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "env") == 0) //fork
		ret = ft_env(env_head);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0) //fork
		ret = ft_echo(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ret = ft_export(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ret = ft_unset(cmd->argc, cmd->argv, env_head);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0) //fork
		ret = ft_exit(cmd->argc, cmd->argv, env_head);
	//else //todo: linux builtin 함수 실행
	//	builtin();
	return (ret);
}

int	is_need_fork(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export"))
		return (0);
	else if (ft_strcmp(cmd, "unset"))
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
		if (arg->redirection)
			break ;
		++i;
	}
}

//ls -l | cat > a > b
//cat > a > b
int	redirection_process(t_arg *arg, t_cmd *cmd)
{
	int	i;
	int	o_flag;

	i = 1;
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
			execute_cmd(cmd, arg->env_head);
		i += 2;
	}
	return (0);
}


int	pipe_process(t_arg *arg, t_cmd *cmd)
{
	(void)arg;
	(void)cmd;
	return (0);
}

int	nomal_process(t_arg *arg, t_cmd *cmd)
{
	execute_cmd(cmd, arg->env_head);
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
	arg->o_flag = 0;
	arg->pid = 0;
	init_env_list(arg->env_head, arg->envp);
	return (0);
}

int	executor(t_cmd *cmd)
{
	t_arg	arg;
	//int	exit_status;

	init_arg(&arg, cmd);
	while (cmd != 0)
	{
		updata_arg(&arg, cmd);
		if (is_need_fork(cmd->argv[0]) == 0)
			execute_cmd(cmd, arg.env_head);
		else
		{
			if (arg.redirection)
				redirection_process(&arg, cmd);
			else if (arg.pipe)
				pipe_process(&arg, cmd);
			else
				nomal_process(&arg, cmd);
		}
		cmd = cmd->next;	
	}
	return (0);
}
