/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:16:02 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 00:57:14 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

int	ft_access(char *tmp_file_name)
{
	int	fd;

	fd = open(tmp_file_name, O_RDONLY);
	close(fd);
	if (fd == -1)
		return (0);
	else
		return (1);
}
