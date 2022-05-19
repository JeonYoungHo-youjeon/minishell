/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:48:13 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 01:53:22 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //chdir
#include <stdlib.h> //free
#include "libft/include/libft.h" 

static int	cd_home(const char *path)
{
	char	*home;

	home = getenv("HOME");
	if (path == 0)
		return (chdir(home));
	else if (ft_strlen(path) == 1 && ft_strncmp("~", path, 1) == 0)
		return (chdir(home));
	else if (ft_strncmp("~/", path, 2) == 0)
	{
		home = ft_strjoin(home, path + 1);
		if (home == NULL)
		{
			//print_error(); ??
			return (-1);
		}
		chdir(home);
		free(home);
	}
	return (0);
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
