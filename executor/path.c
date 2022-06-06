/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:55:17 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 14:57:27 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_path(char **path)
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

	if (is_exist_file(cmd->argv[0]))
		return (ft_strdup(cmd->argv[0]));
	path = ft_split(getenv("PATH"), ':');
	slash = ft_strjoin("/", cmd->argv[0]);
	i = 0;
	while (path[i])
	{
		ret = ft_strjoin(path[i], slash);
		if (is_exist_file(ret))
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
