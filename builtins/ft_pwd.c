/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:54:41 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 03:55:33 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		exit_with_err("getcwd()", strerror(errno), EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	ft_write(STDOUT_FILENO, buf, ft_strlen(buf));
	ft_write(STDOUT_FILENO, "\n", 1);
	free(buf);
	return (EXIT_SUCCESS);
}
