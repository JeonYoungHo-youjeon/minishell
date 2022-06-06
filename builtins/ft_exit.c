/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:14:43 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 19:57:15 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static	int	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || '9' < *str)
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
			print_err3("exit", cmd->argv[1], "numeric argument required");
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(cmd->argv[1]) % 256;
	}
	else if (cmd->argc > 2)
		print_err3("exit", NULL, "too many arguments");
	if (cmd->prev == NULL)
		ft_write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_code);
}
