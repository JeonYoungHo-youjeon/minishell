/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:48:13 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 20:15:58 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	cd_home(char *path)
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
		ret = chdir(home);
		free(home);
	}
	return (ret);
}

int	ft_cd(char *path)
{
	int	ret;

	if (path == 0)				//'cd'
		ret = cd_home(path);
	else if (ft_strncmp("~", path, 1) == 0) //'cd ~', 'cd ~/path'
		ret = cd_home(path);
	else  					//'cd path'
		ret = chdir(path);
	if (ret == -1)
	{
		print_err3("cd", path, strerror(errno));
		ret = EXIT_FAILURE;
	}
	return (ret);
}
