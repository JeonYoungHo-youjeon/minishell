/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/05/28 17:28:50 by mher             ###   ########.fr       */
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
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_arg
{
	char	**envp;
	//char	**path_env;
	//char	**cmd_options;
	char	*infile;
	//char	*outfile;
	char	*append;
	int	heredoc;
	int	pipe;
	int	redirection;
	int	fd1[2];
	int	fd2[2];
	int	o_flag;
	pid_t	pid;

	t_env	*env_head;
}	t_arg;

int	redirect_infile(t_arg *arg, char *infile, int o_flag);
int	redirect_outfile(t_arg *arg, char *outfile, int o_flag);
void	redirect_std_fd(t_arg *arg);
void	close_unused_fd(t_arg *arg);

int	execute_cmd(t_arg *arg, t_cmd *cmd);
int	is_need_fork(char *cmd);
void	updata_arg(t_arg *arg, t_cmd *cmd);
int	redirection_process(t_arg *arg, t_cmd *cmd);
int	pipe_process(t_arg *arg, t_cmd *cmd);
int	nomal_process(t_arg *arg, t_cmd *cmd);
int	executor(t_cmd *cmd);

#endif
