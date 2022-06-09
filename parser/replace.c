/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:44:28 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/09 15:27:28 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*replace_while_dollar(char str, char *new, t_env *head, char **env)
{
	if (ft_isalnum(str) || str == '_')
		*env = ft_strjoin_char(*env, str);
	else if (str == '?' && *env == NULL)
	{
		*env = ft_itoa(g_exit_code);
		new = ft_strjoin(new, *env);
	}
	else
	{
		if (*env != NULL)
		{
			new = ft_strjoin(new, ft_getenv(head, *env));
			*env = ft_free(*env);
		}
		else
			new = ft_strdup("$");
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
	{
		result = ft_strjoin_char(new, c);
	}
	else
	{
		return (new);
	}
	return (result);
}

static int	dollar_check(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '$')
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
		quotes = parse_set_quotes(cmd->argv[i][j], quotes, cmd);
		if (cmd->argv[i][j] == '$' && quotes != 1)
			dollar = 1;
		else if (dollar == 1)
		{
			new = replace_while_dollar(cmd->argv[i][j], new, head, &env);
			dollar = dollar_check(cmd->argv[i][j]);
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

	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			env = NULL;
			new = NULL;
			new = replace_while(cmd, head, env, i);
			if (new == NULL)
				new = ft_strdup("");
			cmd->argv[i] = ft_free(cmd->argv[i]);
			cmd->argv[i] = new;
			i++;
		}
		cmd = cmd->next;
	}
}
