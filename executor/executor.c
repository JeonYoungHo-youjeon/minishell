/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2022/05/26 22:41:02 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "./executor.h"

int	execute_cmd(t_cmd *cmd)
{
	int	ret;

	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ret = ft_cd(cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0) //fork
		ret = ft_pwd();
	else if (ft_strcmp(cmd->argv[0], "env") == 0) //fork
		ret = ft_env(cmd->env_head);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0) //fork
		ret = ft_echo(cmd->argc, cmd->argv, cmd->env_head);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ret = ft_export(cmd->argc, cmd->argv, cmd->env_head);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ret = ft_unset(cmd->argc, cmd->argv, cmd->env_head);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0) //fork
		ret = ft_exit(cmd->argc, cmd->argv, cmd->env_head);
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

int	executor(t_cmd *cmd)
{
	t_arg	arg;

	if (pipe(arg.fd1) < 0)
		return (-1);
	while (cmd != 0)
	{
		if (pipe(arg.fd2) < 0)
			return (-1);
		if (is_need_fork(cmd->argv[0]) == 0)
			executor(cmd);
		else
		{
			redirect_std_fd(&arg, cmd);
			arg.pid = fork();
			if (arg.pid == -1)
				return (-1);
			if (arg.pid == 0)
			{
				close_unused_fd(&arg);
				execute_cmd(cmd);
			}
			else
			{
				close_unused_fd(&arg);
				arg.fd1[0] = arg.fd2[0];
			}
		}
		cmd = cmd->next;	
	}
	return (0);
}
