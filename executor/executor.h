/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/06/08 19:56:09 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READ 0
# define WRITE 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>

# include "../struct/struct.h"
# include "../utiles/utiles.h"
# include "../builtins/builtin.h"

void	executor(t_cmd *cmd, t_env *env_head, char *envp[]);
void	redirect(t_cmd *cmd);
void	heredoc(t_cmd *cmd);
void	close_unused_fd(t_cmd *cmd, pid_t pid);
int		check_valid_syntax(t_cmd *cmd_head);
void	wait_child(void);

char	*get_cmd_path(t_cmd *cmd, t_env *env_head);
void	trim_cmd_argv(t_cmd *cmd, const char *set, int direction);

void	infile_open(t_cmd *cmd);
void	outfile_open(t_cmd *cmd);
char	*get_tmp_file_name(void);
void	delete_tmp_file(void);
void	init_cmd_arg(t_cmd *cmd, t_env *env_head);
void	clear_cmd(t_cmd *cmd_head);

#endif
