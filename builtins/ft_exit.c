/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:14:43 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 03:38:45 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"
#include <stdlib.h>

static	int	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->argc >= 2)
	{
		if (!is_number(cmd->argv[1]))
		{
			print_err2("exit", "numeric argument required");
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(cmd->argv[1]) % 256;
	}
	else if (cmd->argc > 2)
		print_err2("exit", "too many arguments");
	exit(exit_code);
}
