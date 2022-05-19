/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:54:41 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 01:57:43 by mher             ###   ########.fr       */
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
