/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:48:13 by mher              #+#    #+#             */
/*   Updated: 2022/05/19 20:29:25 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //chdir()
#include <stdio.h> //printf
#include <stdlib.h> //free
#include "libft/include/libft.h"

int	ft_pwd(void) //test
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == 0)
	{
		//print_error();
		return (-1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}


void	cd_path(const char *path)
{
	chdir(path);
}

void	cd_home(char *envp[])
{
	while (*envp && ft_strncmp("HOME=", *envp, 5))
		++envp;
	//if (envp == NULL)
	//	error();
	cd_path(*envp + 5);	
}

void	ft_cd(const char *path, char *envp[])
{
	if (path == 0)
		cd_home(envp);
	else if (ft_strlen(path) == 1 && ft_strncmp("~", path, 1) == 0)
		cd_home(envp);
	else
		cd_path(path);
}

int main(int argc, char *argv[], char *envp[]) //test
{
	ft_pwd();
	ft_cd("~", envp);
	ft_pwd();
	return (0);
}
