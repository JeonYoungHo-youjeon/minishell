/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/30 23:26:21 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	cd_test(void)
{
	ft_pwd();
	ft_cd("..");
	ft_pwd();
}

void	env_test(t_env *env_head)
{
	ft_env(env_head);
}

void	pwd_test(void)
{
	ft_pwd();
}

void	echo_test(int argc, char *argv[], t_env *env_head)
{
	ft_echo(argc, argv, env_head);
}

void	exprot_test(int argc, char *argv[], t_env *env_head)
{
	ft_env(env_head);
	printf("------------------------------------\n");
	ft_export(argc, argv, env_head);
	ft_env(env_head);
}

void	unset_test(int argc, char *argv[], t_env *env_head)
{
	ft_env(env_head);
	printf("------------------------------------\n");
	ft_unset(argc, argv, env_head);
	ft_env(env_head);
}

int main(int argc, char *argv[], char *envp[])
{
	t_env	env_head;
	//t_cmd	cmd;

	(void)argc;
	(void)argv;
	if (init_env_list(&env_head, envp) == -1)
		return (-1);
	//env_test(&env_head);
	//exprot_test(argc, argv, &env_head);
	//unset_test(argc, argv, &env_head);
	//echo_test(argc, argv, &env_head);
	//pwd_test();
	//cd_test();

	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;

	cmd1.argc = 7;
	cmd1.argv = ft_split("< infile cat >> a >  b", ' ');
	cmd1.envp = envp;
	cmd1.is_pipe = 1;
	cmd1.prev = 0;
	cmd1.next = &cmd2;
	//cmd1.next = 0;

	cmd2.argc = 2;
	cmd2.argv = ft_split("cat b", ' ');
	cmd2.envp = envp;
	cmd2.is_pipe = 1;
	cmd2.prev = &cmd1;
	cmd2.next = &cmd3;

	cmd3.argc = 2;
	cmd3.argv = ft_split("grep h", ' ');
	cmd3.envp = envp;
	cmd3.is_pipe = 0;
	cmd3.prev = &cmd2;
	cmd3.next = 0;

	executor(&cmd1, &env_head);
	return (0);
}
