/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:44:28 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 16:32:38 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*replace_while_dollar(char str, char *new, t_env *head, char *env)
{
	if (ft_isalnum(str) || str == '_')
		env = ft_strjoin_char(env, str);
	else if (str == '?' && env == NULL)
	{
		env = ft_itoa(g_exit_code);
		new = ft_strjoin(new, env);
	}
	else
	{
		new = ft_strjoin(new, ft_getenv(head, env));
		env = ft_free(env);
	}
	return (new);
}

static char	*replace_while_else(char c, char *new, int quotes)
{
	char	*result;

	result = NULL;
	if (c == -32)
		result = ft_strjoin_char(new, ' ');
	else if (!(c == '\"' && quotes != 1) && !(c == '\'' && quotes != 2))
		result = ft_strjoin_char(new, c);
	return (result);
}

static int	dollar_check(char c)
{
	if (ft_isalnum(c) || c == '_' || c != '$')
		return (1);
	else
		return (0);
}

static char	*replace_while(t_cmd *cmd, t_env *head, char *env, int i)
{
	int		j;
	char	*new;
	int		dollar;
	int		quotes;

	quotes = 0;
	dollar = 0;
	j = 0;
	new = NULL;
	while (j <= (int)ft_strlen(cmd->argv[i]))
	{
		quotes = parse_set_quotes(cmd->argv[i][j], quotes);
		if (cmd->argv[i][j] == '$' && quotes != 1 && dollar == 0)
			dollar = 1;
		else if (dollar == 1)
		{
			new = replace_while_dollar(cmd->argv[i][j], new, head, env);
			if (!(dollar_check(cmd->argv[i][j])))
				dollar = 0;
		}
		else
			new = replace_while_else(cmd->argv[i][j], new, quotes);
		j++;
	}
	return (new);
}

void	replace(t_cmd *cmd, t_env *head)
{
	int		i;
	char	*new;
	char	*env;

	i = 0;
	new = NULL;
	env = NULL;
	while (cmd)
	{
		while (i < cmd->argc)
		{
			new = replace_while(cmd, head, env, i);
			cmd->argv[i] = ft_free(cmd->argv[i]);
			cmd->argv[i] = new;
			new = NULL;
			i++;
		}
		cmd = cmd->next;
	}
}