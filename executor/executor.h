/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/05/29 02:46:29 by mher             ###   ########.fr       */
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

typedef struct s_arg
{
	char	*infile;
	char	*append;
	int	heredoc;
	int	pipe;
	int	redirection;
	int	o_flag;
	pid_t	pid;
}	t_arg;


int	is_need_fork(char *cmd);
int	execute_cmd(t_cmd *cmd, t_env *env_head);
int	executor(t_cmd *cmd);

char	*get_path_cmd(char **path_env, char *cmd);

#endif
