/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:55:17 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 03:58:54 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_cmd_path(t_cmd *cmd)
{
	int	i;
	char	*ret;
	char	*slash;
	char	**path;

	cmd->cmd_path = NULL;
	if (access(cmd->argv[0], X_OK) == 0)
	{
		cmd->cmd_path = cmd ->argv[0];
		return (0);
	}
	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (-1);
	slash = ft_strjoin("/", cmd->argv[0]);
	if (slash == NULL)
		return (-1);
	i = 0;
	while (path[i])
	{
		ret = ft_strjoin(path[i], slash);
		if (ret == NULL)
			return (-1);
		if (access(ret, X_OK) == 0)
			break ;
		free(ret);
		++i;
	}
	free(slash);
	i = 0;
	while(path[i])
		free(path[i++]);
	free(path);
	cmd->cmd_path = ret;
	return (0);
}
