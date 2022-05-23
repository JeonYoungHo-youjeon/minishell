/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:15:58 by mher              #+#    #+#             */
/*   Updated: 2022/05/23 16:37:33 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

char	**copy_env(char **envp)
{
	int	i;
	size_t	j;
	int	len;
	char	**ret;
	
	len = 0;
	while (envp[len])
		++len;
	ret = (char **)malloc(len * sizeof(char *) + 1);
	i = 0;
	while (i < len)
	{
		ret[i] = (char *)malloc(ft_strlen(envp[i]) * sizeof(char) + 1);
		j = 0;
		while (j <= ft_strlen(envp[i]))
		{
				ret[j] = envp[j];
				++j;
		}
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

static char	*get_env_key(char *env)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while(env[len] != '=')
		++len;
	key = (char *)malloc(len * sizeof(char) + 1);
	if (key == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = env[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

static char	*get_env_value(char *env)
{
	size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while(*env != '=')
		++env;
	len = ft_strlen(++env);
	value = (char *)malloc(len * sizeof(char) + 1);
	if (value == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		value[i] = env[i];
		++i;
	}
	value[i] = 0;
	return (value);
}

int	init_env(t_env *env_head, char **envp)
{
	size_t	i;
	t_env	*cur;
	t_env	*new;

	cur = env_head;
	i = 0;
	cur->next = 0;
	cur->prev = 0;
	cur->key = get_env_key(envp[i]);
	if (cur->key == 0)
		return (-1);
	cur->value = get_env_value(envp[i]);
	if (cur->value == 0)
		return (-1);
	while (envp[++i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (new == 0)
			return (-1);
		new->key = get_env_key(envp[i]);
		if (new->key == 0)
			return (-1);
		new->value = get_env_value(envp[i]);
		if (new->value == 0)
			return (-1);
		cur->next = new;
		new->prev = cur;
		cur = cur->next;
	}
	cur->next = 0;
	return (0);
}
