/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/23 22:27:54 by mher             ###   ########.fr       */
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

void	echo_test(int argc, char *argv[], char *envp[])
{
	ft_echo(argc, argv, envp);
}

void	exprot_test(char **envp, char *key_value, t_env *env_head)
{
	char **tmp;
	char **new;

	tmp = copy_env(envp);
	ft_env(env_head);
	//ft_env(tmp);
	new = ft_export(tmp, key_value);
	ft_env(env_head);
	free(new);
	//ft_env(new);
}

void	unset_test(char **envp, t_env *env_head)
{
	char **tmp;
	char **new;

	tmp = copy_env(envp);
	ft_env(env_head);
	//ft_env(tmp);
	new = ft_export(tmp, "TEST=1234");
	//ft_env(new);
	ft_env(env_head);
	printf("------------------------------------\n");
	ft_unset(&new, "TEST");
	ft_env(env_head);
	//ft_env(new);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	t_env	env_head;
	t_env	*cur;

	if (init_env(&env_head, envp) == -1)
		return (-1);
	cur = &env_head;
	env_test(&env_head);
	//unset_test(envp);
	return (0);
}
