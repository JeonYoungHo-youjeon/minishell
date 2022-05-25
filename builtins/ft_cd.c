/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:48:13 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 22:33:25 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	cd_home(const char *path)
{
	char	*home;
	int	ret;

	home = getenv("HOME");
	ret = -1;
	if (path == 0)
		return (chdir(home));
	else if (ft_strlen(path) == 1 && ft_strncmp("~", path, 1) == 0)
		return (chdir(home));
	else if (ft_strncmp("~/", path, 2) == 0)
	{
		home = ft_strjoin(home, path + 1);
		if (home == NULL)
		{
			//perror(); ??
			return (-1);
		}
		ret = chdir(home);
		free(home);
	}
	return (ret);
}

int	ft_cd(const char *path)
{
	//'cd'
	if (path == 0)		
		return (cd_home(path));
	//'cd ~', 'cd ~/path'
	else if (ft_strncmp("~", path, 1) == 0) 
		return (cd_home(path));
	//'cd path'
	else
		return (chdir(path));
}
