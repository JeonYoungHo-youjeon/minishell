/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/05/31 00:40:45 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READ 0
# define WRITE 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "./builtins/builtin.h"
# include "./libft/include/libft.h"

typedef struct	s_cmd
{
	int		argc;
	char		**argv;
	char		**envp;
	int		is_pipe;
	int		fd[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

int	executor(t_cmd *cmd, t_env *env_head);
int	redirect(t_cmd *cmd);
int	close_unused_fd(t_cmd *cmd, pid_t pid);
char	*get_cmd_path(char *cmd, char **path);

#endif
