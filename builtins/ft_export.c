/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:05:45 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 22:52:20 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	append_env(t_env *env, char *key, char *value)
{
	t_env	*new;

	new = new_env(NULL);
	if (new == NULL)
		return (-1);
	new->prev = env;
	env->next = new;
	env->key = key;
	env->value = value;
	return (0);
}

static int	change_env(t_env *env, char *value)
{
	free(env->value);
	env->value = value;
	return (0);
}

int	ft_export(t_env *env_head, char *key_value)
{
	int	i;
	t_env	*env;
	char	*key;
	char	*value;

	//key_value 인자가 "kye=value" 형태인지get_env_key(), get_env_value()
	//함수에서 검사 해줌
	key = get_env_key(key_value);
	if (key == NULL)
		return (0);
	value = get_env_value(key_value);
	if (value == NULL)
		return (0);
	i = 0;
	while (ft_isdigit(key[i]))
		++i;
	if (key[i] == 0) // kye 에 숫자만 들어가는 경우 종료
		return (0);
	env = compare_env_key(env_head, key);
	if (env->key != 0) //key가 존재 하는경우 value 만 변경
		return (change_env(env, value));
	else // key가 존재하지 않는 경우 환경변수 마지막에 추가
		return (append_env(env, key, value));
}
