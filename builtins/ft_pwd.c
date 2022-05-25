/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:54:41 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 22:17:12 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == 0)
	{
		//print_error(); ??
		return (-1);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	free(buf);
	return (0);
}
