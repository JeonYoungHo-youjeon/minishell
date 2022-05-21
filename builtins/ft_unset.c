/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:17:22 by mher              #+#    #+#             */
/*   Updated: 2022/05/21 20:30:19 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	get_key_len(char *key)
{
	int	len;

	len = 0;
	while(key[len])
		++len;
	return (len);
}

static int	find_key_idx(char *key, char **envp)
{
	int	i;
	int	key_len;
	
	i = 0;
	key_len = get_key_len(key);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], key_len) == 0)
			if (envp[i][key_len] == '=')
				return (i);
		++i;
	}
	return (-1);
}

static void	remove_env(char ***envp, int idx)
{
	while ((*envp)[idx + 2])
	{
		(*envp)[idx] = (*envp)[idx + 1];
		++idx;
	}
}

void	ft_unset(char ***envp, char *key)
{
	int	idx;
	
	idx = find_key_idx(key, *envp);
	if (idx == -1)
		return ;
	else
		return (remove_env(envp, idx));
}
