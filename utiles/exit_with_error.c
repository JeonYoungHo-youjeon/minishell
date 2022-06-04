/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:04:24 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 02:05:16 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

void	exit_with_err(char *str1, char *str2, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(exit_code);
}

void	print_err(char *cmd, char *str1, char *err_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (str1)
	{	
		ft_putstr_fd(str1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
