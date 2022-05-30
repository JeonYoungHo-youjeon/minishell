/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/30 18:12:08 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

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
	printf("%s\n",ft_getenv(&env_head, "PWD"));

	return (0);
}
