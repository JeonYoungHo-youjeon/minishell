/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/25 00:00:16 by mher             ###   ########.fr       */
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

void	exprot_test(t_env *env_head, char *key_value)
{
	ft_env(env_head);
	printf("------------------------------------\n");
	ft_export(env_head, key_value);
	ft_env(env_head);
}

void	unset_test(t_env *env_head)
{
	ft_env(env_head);
	printf("------------------------------------\n");
	ft_unset(env_head, "test");
	ft_env(env_head);
}

int main(int argc, char *argv[], char *envp[])
{
	t_env	env_head;

	(void)argc;
	(void)argv;
	if (init_env_list(&env_head, envp) == -1)
		return (-1);
	env_test(&env_head);
	//exprot_test(&env_head, argv[1]);
	//unset_test(&env_head);
	//echo_test(argc, argv, &env_head);
	//pwd_test();
	//cd_test();
	return (0);
}
