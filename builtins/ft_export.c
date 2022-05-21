/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:05:45 by mher              #+#    #+#             */
/*   Updated: 2022/05/21 17:40:40 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	get_key_len(char *key_value)
{
	int	len;

	len = 0;
	while(key_value[len] != '=')
		++len;
	return (len);
}

static int	find_key_idx(char *key_value, char **envp)
{
	int	i;
	int	key_len;
	
	i = 0;
	key_len = get_key_len(key_value);
	while (envp[i] && ft_strncmp(key_value, envp[i], key_len + 1))
		++i;
	if (envp[i] == NULL)
		return (0);
	return (i);
}

static char	**append_env(char **envp, char *key_value)
{
	int	i;
	char	**new_envp;
	char	**tmp;

	i = 0;
	while (envp[i])
		++i;
	new_envp = (char **)malloc(i * sizeof(char *) + 2);
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		++i;
	}
	new_envp[i++] = key_value;
	new_envp[i] = NULL;
	tmp = envp;
	envp = new_envp;
	free(tmp);
	return (new_envp);
}

static char	**change_env(char **envp, char *key_value, int idx)
{
	free(envp[idx]);
	envp[idx] = key_value; 
	return (envp);
}

char	**ft_export(char **envp, char *key_value)
{
	int	idx;
	
	idx = find_key_idx(key_value, envp);
	if (idx != 0)
		return (change_env(envp, key_value, idx));
	else
		return (append_env(envp, key_value));
}
