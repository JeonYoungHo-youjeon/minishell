/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/05/26 22:42:05 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READ 0
# define WRITE 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../builtins/builtin.h"

typedef struct	s_cmd
{
	int		argc;
	char		**argv;
	int		pipe;
	int		heredoc;
	int		append;
	char		*input;
	char		*output;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	t_env		*env_head; //??
}	t_cmd;

typedef struct s_arg
{
	int	fd1[2];
	int	fd2[2];
	pid_t	pid;
	int	o_flag;
}	t_arg;

void	redirect_std_fd(t_arg *arg, t_cmd *cmd);
void	close_unused_fd(t_arg *arg);

#endif
