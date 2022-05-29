/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:55:17 by mher              #+#    #+#             */
/*   Updated: 2022/05/28 21:18:45 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_path_cmd(char **path_env, char *cmd)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		return (NULL);
	while (path_env[i])
	{
		ret = ft_strjoin(path_env[i], tmp);
		if (ret == NULL)
			return (NULL);
		if (access(ret, X_OK) == 0)
		{
			free(tmp);
			return (ret);
		}
		free(ret);
		i++;
	}
	free(tmp);
	return (NULL);
}
