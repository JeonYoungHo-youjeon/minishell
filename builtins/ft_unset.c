/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:17:22 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 22:53:57 by mher             ###   ########.fr       */
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
}

void	ft_unset(t_env *env_head, char *key)
{
	t_env	*env;
	
	env = compare_env_key(env_head, key);
	if (env->key == NULL)
		return ;
	else
		return (remove_env(env));
}
