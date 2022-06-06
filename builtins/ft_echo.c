/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:36:23 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 18:50:56 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	is_option_n(char *str)
{
	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	++str;
	while (*str == 'n')
		str++;
	if (*str != 0)
		return (0);
	return (1);
}

static int	check_option_n(int argc, char *argv[], int *idx)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (argc < 2)
		return (0);
	option_n = is_option_n(argv[i]);
	while (i < argc && is_option_n(argv[i])) 
		++i;
	*idx = i;
	return (option_n);
}

static int	check_infile_redirection(char *argv[], int *idx)
{
	if (ft_strcmp(argv[*idx], "<"))
		return (0);
	*idx += 2;
	return (1);
}

int	ft_echo(int argc, char *argv[])
{
	int	idx;
	int	option_n;

	idx = 1;
	option_n = check_option_n(argc, argv, &idx);
	while (idx < argc)
	{
		if (check_infile_redirection(argv, &idx) == 1)
			continue ;
		ft_write(STDOUT_FILENO, argv[idx], ft_strlen(argv[idx]));
		if (idx + 1 != argc)
			ft_write(STDOUT_FILENO, " ", 1);
		++idx;
	}
	if (option_n == 0)
		ft_write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
