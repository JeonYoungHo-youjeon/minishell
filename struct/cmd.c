/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:00:29 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 16:27:29 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

t_cmd	*ft_list_init(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->argc = 0;
	new_mem->argv = NULL;
	new_mem->fd[0] = 0;
	new_mem->fd[1] = 0;
	new_mem->is_pipe = false;
	new_mem->next = NULL;
	new_mem->prev = NULL;
	return (new_mem);
}

void	ft_free_list(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			cmd->argv[i] = ft_free(cmd->argv[i]);
			i++;
		}
		cmd->argv = ft_free(cmd->argv);
		ptr = cmd;
		cmd = cmd->next;
		ptr = ft_free(ptr);
	}
}