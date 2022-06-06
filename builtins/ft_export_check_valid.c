/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_check_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:09:05 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 14:11:12 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_all_digit(char *key_value)
{
	while (*key_value && *key_value != '=')
	{
		if (!ft_isdigit(*key_value))
			break ;
		++key_value;
	}
	if (*key_value == '=')
		return (1);
	return (0);
}

static	int	is_have_equal_character(char *key_value)
{
	while (*key_value)
	{
		if (*key_value == '=')
			break ;
		++key_value;
	}
	if (*key_value == '\0')
		return (0);
	return (1);
}

int	check_valid_identifier(int argc, char *argv[])
{
	int	i;

	i = 1;
	while(i < argc)
	{
		if (!is_have_equal_character(argv[i]))
		{
			print_err3("export", argv[i], "not a valid identifier");
			return (-1);
		}
		if (is_all_digit(argv[i]))
		{
			print_err3("export", argv[i], "not a valid identifier");
			return (-1);
		}
		i++;
	}
	return (0);
}
