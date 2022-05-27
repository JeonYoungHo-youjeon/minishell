/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/27 19:30:08 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "./executor.h"

int	execute_cmd(t_cmd *cmd, t_env *env_head)
{
	int	ret;

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
	size_t	i;

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
	size_t	i;
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
{}

int	nomal_process(t_arg *arg, t_cmd *cmd)
{}

int	executor(t_cmd *cmd)
{
	t_arg	arg;
	int	exit_status;

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
			cmd = cmd->next;	
		}
	}
	return (0);
}

		//if (pipe(arg.fd2) < 0)
		//	return (-1);
		//if (is_need_fork(cmd->argv[0]) == 0)
		//	executor(cmd);
		//else
		//{
		//	redirect_std_fd(&arg);
		//	arg.pid = fork();
		//	if (arg.pid == -1)
		//		return (-1);
		//	if (arg.pid == 0)
		//	{
		//		close_unused_fd(&arg);
		//		execute_cmd(cmd, arg.env_head);
		//	}
		//	else
		//	{
		//		close_unused_fd(&arg);
		//		arg.fd1[0] = arg.fd2[0];
		//	}
		//}
