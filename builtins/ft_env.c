/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:37:24 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 23:01:09 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

void	ft_env(t_env *cur)
{
	while (cur->key != 0)
	{
		write(STDOUT_FILENO, cur->key, ft_strlen(cur->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
}
