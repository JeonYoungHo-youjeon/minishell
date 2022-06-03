/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:14:43 by mher              #+#    #+#             */
/*   Updated: 2022/06/03 19:00:14 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

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

int	ft_exit(t_cmd *cmd, t_env *env_head)
{
	int	exit_code;

	(void)env_head;
	exit_code = EXIT_SUCCESS;
	if (cmd->argc >= 2)
	{
		if (!is_number(cmd->argv[1]))
		{
			perror("numeric argument required");
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(cmd->argv[1]) % 256;
	}
	else if (cmd->argc > 2)
	{
		perror("too many arguments");
		exit_code = EXIT_FAILURE;
	}
	//return (exit_code);
	exit(exit_code); //TEST
}
