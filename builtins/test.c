/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/23 17:48:17 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

void	cd_test(void)
{
	ft_pwd();
	ft_cd("..");
	ft_pwd();
}

void	env_test(char *envp[])
{
	ft_env(envp);
}

void	pwd_test(void)
{
	ft_pwd();
}

void	echo_test(int argc, char *argv[], char *envp[])
{
	ft_echo(argc, argv, envp);
}

void	exprot_test(char **envp, char *key_value)
{
	char **tmp;
	char **new;

	tmp = copy_env(envp);
	ft_env(tmp);
	new = ft_export(tmp, key_value);
	ft_env(new);
	free(new);
}

void	unset_test(char **envp)
{
	char **tmp;
	char **new;

	tmp = copy_env(envp);
	ft_env(tmp);
	new = ft_export(tmp, "TEST=1234");
	ft_env(new);
	printf("------------------------------------\n");
	ft_unset(&new, "TEST");
	ft_env(new);
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
	while (cur != 0)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	//unset_test(envp);
	return (0);
}
