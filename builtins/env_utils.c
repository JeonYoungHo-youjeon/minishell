/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:15:58 by mher              #+#    #+#             */
/*   Updatej: 2022/05/24 19:17:39 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

char	*get_env_key(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while(key_value[len] != 0 && key_value[len] != '=')
		++len;
	if (key_value[len] == '\0')
		return (NULL);
	key = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = key_value[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*get_env_value(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while(key_value[len] != 0 && key_value[len] != '=')
		++key_value;
	if (key_value[len] == 0)
		return (NULL);
	len = ft_strlen(++key_value);
	value = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		value[i] = key_value[i];
		++i;
	}
	value[i] = 0;
	return (value);
}

t_env	*compare_env_key(t_env *env_head, char *key)
{
	t_env	*cur;
	
	cur = env_head;
	while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
		cur = cur->next;
	return (cur);
}

t_env	*new_env(char *key_value)
{
	t_env	*new;
	
	new = (t_env *)ft_malloc(sizeof(t_env), 1);
	if (key_value == NULL)
	{
		new->key = 0;
		new->value = 0;
		new->next = 0;
		new->prev = 0;
	}
	else 
	{
		new->key = get_env_key(key_value);
		if (new->key == NULL)
			return (NULL);
		new->value = get_env_value(key_value);
		if (new->value == NULL)
			return (NULL);
		new->next = 0;
		new->prev = 0;
	}
	return (new);
}

int	init_env_list(t_env *cur, char **envp)
{
	size_t	i;
	t_env	*new;

	i = 0;
	cur->key = get_env_key(envp[i]);
	if (cur->key == NULL)
		return (-1);
	cur->value = get_env_value(envp[i]);
	if (cur->value == NULL)
		return (-1);
	cur->next = 0;
	cur->prev = 0;
	while (envp[++i])
	{
		new = new_env(envp[i]);
		if (new == NULL)
			return (-1);
		cur->next = new;
		new->prev = cur;
		cur = cur->next;
	}
	new = new_env(NULL);
	new->prev = cur;
	cur->next = new;
	return (0);
}
