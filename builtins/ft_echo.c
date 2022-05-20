/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:36:23 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 20:33:19 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

static int	check_option_n(int argc, char *argv[], int *idx)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
	if (argc < 2)
		return (n_option);
	while (i < argc && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		n_option = 1;
		++i;
	}
	*idx = i;
	return (n_option);
}

static void	echo_env_value(const char *key, char *envp[])
{
	char	*value;
	(void)envp;

//todo: exit_status를 전역변수로 받으면 이런식으로 처리 가능
//	if (key[1] == '?')
//		print_exit_status();
//	else
//	{
		value = getenv(key); //todo: minishell 자체 ft_getenv() 로 바꿔야함
		write(STDOUT_FILENO, value, ft_strlen(value));
//	}
//
//	else
//	{
//		value = ft_getenv(key, envp);
//	}
}

int	ft_echo(int argc, char *argv[], char *envp[])
{
	int	i;
	int	n_option;

	i = 1;
	n_option = check_option_n(argc, argv, &i);
	while (i < argc)
	{
		if (argv[i][0] == '$')
			echo_env_value(argv[i], envp);
		else
			write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (i + 1 != argc)
			write(STDOUT_FILENO, " ", 1);
		++i;
	}
	if (n_option == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
