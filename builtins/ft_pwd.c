/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:54:41 by mher              #+#    #+#             */
/*   Updated: 2022/05/19 18:18:34 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //getcwd
#include <stdio.h> //printf
#include <stdlib.h> //free

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == 0)
	{
		//print_error(); ??
		return (-1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	main(void)
{
	ft_pwd();
	return (0);
}
