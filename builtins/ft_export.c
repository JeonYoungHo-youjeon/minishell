/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:05:45 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 18:31:27 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	append_env(t_env *env, char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == 0)
		return (-1);
	new->key = 0;
	new->value = 0;
	new->next = 0;
	new->prev = env;

	env->key = key;
	env->value = value;
	env->next = new;
	return (0);
}

static int	change_env(t_env *env, char *value)
{
	free(env->value);
	env->value = value;
	return (0);
}

// malloc 에러 -1
// 정상 종료 0
int	ft_export(t_env *env_head, char *key, char *value)
{
	int	i;
	t_env	*env;

	// kye 에 숫자만 들어가는 경우 체크
	i = 0;
	while (ft_isdigit(key[i]))
		++i;
	if (key[i] == 0)
		return (0);
	env = compare_env_key(env_head, key);
	if (env->key != 0)
		return (change_env(env, value));
	else
		return (append_env(env, key, value));
}
