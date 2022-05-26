/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:17:22 by mher              #+#    #+#             */
/*   Updated: 2022/05/26 18:07:00 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static void	remove_env(t_env *env)
{
	t_env	*next;
	t_env	*prev;

	next = env->next;
	prev = env->prev;
	prev->next = env->next;
	next->prev = env->prev;
	free(env->key);
	free(env->value);
	free(env);
}

static void	unset(t_env *env_head, char *key)
{
	t_env	*env;
	
	env = compare_env_key(env_head, key);
	if (env->key == NULL)
		return ;
	else
		remove_env(env);
}

int	ft_unset(int argc, char *argv[], t_env *env_head)
{
	int	i;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		unset(env_head, argv[i]);
		++i;
	};
	return (0);
}
