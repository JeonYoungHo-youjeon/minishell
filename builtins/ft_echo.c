/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:36:23 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 22:53:25 by mher             ###   ########.fr       */
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
	int	n_option;

	i = 1;
	n_option = 0;
	if (argc < 2)
		return (0);
	n_option = is_option_n(argv[i]);
	while (i < argc && is_option_n(argv[i])) 
		++i;
	*idx = i;
	return (n_option);
}

static void	echo_env_value(const char *key, char *envp[])
{
	char	*value;
	(void)envp;

//	todo: exit_status를 전역변수로 받으면 이런식으로 처리 가능
//	if (key[1] == '?')
//		print_exit_status();
//	else
//	{
//		todo: minishell 자체 ft_getenv() 로 바꿔야함
		value = getenv(key); 
		write(STDOUT_FILENO, value, ft_strlen(value));
//	}
//
//	else
//	{
//		value = ft_getenv(key, envp);
//		write(STDOUT_FILENO, value, ft_strlen(value));
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
