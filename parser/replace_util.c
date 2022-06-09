/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:11:34 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/09 18:12:55 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_argv(t_cmd *cmd, int *i)
{
	int		tmp;

	tmp = *i;
	printf("tmp : %d\n", tmp);
	while (tmp < cmd->argc - 1)
	{
		cmd->argv[tmp] = cmd->argv[tmp + 1];
		tmp++;
	}
	cmd->argv[tmp] = ft_free(cmd->argv[tmp]);
	*i = *i - 1;
	cmd->argc = cmd->argc - 1;
	cmd->is_dollar = false;
}
