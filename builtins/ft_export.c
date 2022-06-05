/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:05:45 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 20:17:53 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

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

static t_env	*dup_env(t_env *cur)
{
	t_env	*new;

	new = (t_env *)ft_malloc(sizeof(t_env), 1);
	if (cur == NULL)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->key = ft_strdup(cur->key);
		new->value = ft_strdup(cur->value);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

static t_env	*dup_env_list(t_env *cur)
{
	t_env	*ret;
	t_env	*new;
	t_env	*tmp;

	ret =  dup_env(cur);
	tmp = ret;
	cur = cur->next;
	while (cur->key)
	{
		new = dup_env(cur);
		tmp->next = new;
		new->prev = tmp;
		tmp = new;
		cur = cur->next;
	}
	new = dup_env(NULL);
	tmp->next = new;
	new->prev = tmp;
	return (ret);
}

static void	swap_env(t_env *env1, t_env *env2)
{
	char	*tmp_k;
	char	*tmp_v;
	
	tmp_k = env1->key;
	tmp_v = env1->value;
	env1->key = env2->key;
	env1->value = env2->value;
	env2->key = tmp_k;
	env2->value = tmp_v;
}

static void	sort_env_list(t_env *head)
{
	t_env	*cur;

	cur = head;
	while(cur->next->key)
	{
		if (ft_strcmp(cur->key, cur->next->key) > 0)
		{
			swap_env(cur, cur->next);
			cur = head;
		}
		else
			cur = cur->next;
	}
}

static void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env->key)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
	free(env->key);
	free(env->value);
	free(env);
}

static int	export_no_arg(t_env *env_head)
{
	t_env	*tmp;
	t_env	*cur;

	tmp = dup_env_list(env_head);
	sort_env_list(tmp);
	cur = tmp;
	while (cur->key)
	{
		ft_write(STDOUT_FILENO, "declare -x ", 11);
		ft_write(STDOUT_FILENO, cur->key, ft_strlen(cur->key));
		ft_write(STDOUT_FILENO, "=", 1);
		ft_write(STDOUT_FILENO, "\"", 1);
		ft_write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
		ft_write(STDOUT_FILENO, "\"", 1);
		ft_write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	free_env_list(tmp);
	return (EXIT_SUCCESS);
}

int	ft_export(int argc, char *argv[], t_env *env_head)
{
	int	i;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (check_valid_identifier(argc, argv) == -1)
		exit_code = EXIT_FAILURE;
	else if (argc == 1)
		exit_code = export_no_arg(env_head);
	else
	{
		i = 1;
		while (i < argc)
		{
			export(env_head, argv[i]);
			++i;
		}
	}
	return (exit_code);
}
