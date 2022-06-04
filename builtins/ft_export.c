/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:05:45 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 03:50:56 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"
#include <stdlib.h>

static void	append_env(t_env *env, char *key, char *value)
{
	t_env	*new;

	new = new_env(NULL);
	new->prev = env;
	env->next = new;
	env->key = key;
	env->value = value;
	return ;
}

static void	change_env(t_env *env, char *value)
{
	free(env->value);
	env->value = value;
	return ;
}

static void	export(t_env *env_head, char *key_value)
{
	t_env	*env;
	char	*key;
	char	*value;

	key = get_env_key(key_value);
	value = get_env_value(key_value);
	env = compare_env_key(env_head, key);
	if (env->key != 0) //key가 존재 하는경우 value 만 변경
		change_env(env, value);
	else // key가 존재하지 않는 경우 환경변수 마지막에 추가
		append_env(env, key, value);
	return ;
}

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

static int	check_valid_identifier(int argc, char *argv[])
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

static int	export_no_arg(t_env *env_head)
{
	while (env_head->key)
	{
		env_head = env_head->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(int argc, char *argv[], t_env *env_head)
{
	int	i;

	if (check_valid_identifier(argc, argv) == -1)
		return (EXIT_FAILURE);
	if (argc == 1)
		return (export_no_arg(env_head)); //TODO: 완성해야함
	i = 1;
	while (i < argc)
	{
		export(env_head, argv[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}
