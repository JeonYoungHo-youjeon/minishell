/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system_calls2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:54:53 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 16:09:51 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

int	ft_write(int fd, const void *buf, size_t byte)
{
	int	ret;

	ret = write(fd, buf, byte);
	if (ret == -1)
		exit_with_err("write()", strerror(errno), EXIT_FAILURE);
	return (ret);
}

void	*ft_malloc(size_t size, size_t n)
{
	void	*ret;

	ret = malloc(size * n);
	if (ret == NULL)
		exit_with_err("malloc()", strerror(errno), EXIT_FAILURE);
	return (ret);
}

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (execve(file, argv, envp) == -1)
		exit_with_err("execve()", strerror(errno), EXIT_FAILURE);
	return ;
}
