/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:55:17 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 02:18:09 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while(path[i])
		free(path[i++]);
	free(path);
}

char	*get_cmd_path(t_cmd *cmd)
{
	int	i;
	char	*ret;
	char	*slash;
	char	**path;

	if (ft_access(cmd->argv[0]))
		return (ft_strdup(cmd->argv[0]));
	path = ft_split(getenv("PATH"), ':');
	slash = ft_strjoin("/", cmd->argv[0]);
	i = 0;
	while (path[i])
	{
		ret = ft_strjoin(path[i], slash);
		if (ft_access(ret))
			break ;
		free(ret);
		++i;
	}
	free(slash);
	free_path(path);
	if (path[i] == NULL)
		ret = NULL;
	return (ret);
}
