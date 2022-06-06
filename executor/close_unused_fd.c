/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_unused_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:48:43 by mher              #+#    #+#             */
/*   Updated: 2022/06/06 14:48:56 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_unused_fd(t_cmd *cmd, pid_t pid)
{
	if (pid == 0)
		ft_close(cmd->fd[READ]);
	else
		ft_close(cmd->fd[WRITE]);
	return ;
}
