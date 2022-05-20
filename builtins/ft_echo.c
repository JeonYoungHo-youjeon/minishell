/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:36:23 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 19:31:24 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

int	ft_echo(int argc, char *args[], char *envp[]) 
{
	int	i;
	int	n_option;

	(void)envp;
	i = 1;
	n_option = 0;
	if (ft_strncmp(args[i], "-n", 2) == 0)
	{
		n_option = 1;
		i = 2;
	}
	while (i < argc)
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (i + 1 != argc)
			write(STDOUT_FILENO, " ", 1);
		++i;
	}
	if (n_option == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
