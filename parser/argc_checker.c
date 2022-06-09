/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:57:20 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/09 21:54:33 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	first(t_cmd *tmp, t_cmd **ptr, t_cmd **head)
{
	tmp = (*ptr)->next;
	printf("test %p\n", tmp);
	tmp->prev = NULL;
	printf("test %p\n", *head);
	*head = ft_free(*head);
	*head = tmp;
	*ptr = tmp;
	printf("test %p\n", *ptr);
}

void	argc_checker(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	tmp = NULL;
	ptr = *cmd;
	while (ptr)
	{
		if (ptr->prev == NULL && ptr->next == NULL)
			return ;
		if (ptr->argc == 0 && ptr->prev == NULL)
			first(tmp, &ptr, cmd);
		else if (ptr->argc == 0)
		{
			tmp = ptr->prev;
			tmp->next = ptr->next;
			ptr = ft_free(ptr);
			ptr = tmp->next;
			if (ptr)
				ptr->prev = tmp;
		}
		else
			ptr = ptr->next;
	}
}
