/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:48:13 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 18:12:25 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	cd_home(const char *path)
{
	char	*home;
	int	ret;

	home = getenv("HOME");
	if (path == 0)
		ret = chdir(home);
	else if (ft_strlen(path) == 1 && ft_strncmp("~", path, 1) == 0)
		ret = chdir(home);
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
	if (path == 0)
		return (cd_home(path));
	else if (ft_strncmp("~", path, 1) == 0)
		return (cd_home(path));
	else
		return (chdir(path));
}
