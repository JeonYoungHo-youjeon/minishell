/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:36:23 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 22:21:40 by mher             ###   ########.fr       */
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

static void	echo_env_value(t_env *env_head, char *key)
{
	t_env	*env;

	env = compare_env_key(env_head, key);
	if (env->key == NULL)
		return ;
//	todo: exit_status를 전역변수로 받으면 이런식으로 처리 할듯?
//	if (key[1] == '?')
//		print_exit_status();
//	else
//	{
	write(STDOUT_FILENO, env->value, ft_strlen(env->value));
//	}
}

int	ft_echo(int argc, char *argv[], t_env *env_head)
{
	int	idx;
	int	option_n;

	idx = 1;
	option_n = check_option_n(argc, argv, &idx);
	while (idx < argc)
	{
		if (argv[idx][0] == '$')
			echo_env_value(env_head, argv[idx] + 1);
		else
			write(STDOUT_FILENO, argv[idx], ft_strlen(argv[idx]));
		if (idx + 1 != argc)
			write(STDOUT_FILENO, " ", 1);
		++idx;
	}
	if (option_n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
