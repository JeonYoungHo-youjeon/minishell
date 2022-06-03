/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/06/04 04:07:34 by mher             ###   ########.fr       */
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

# include "../struct.h"
# include "../utiles/utiles.h"
# include "../builtins/builtin.h"

int	executor(t_cmd *cmd, t_env *env_head, char *envp[]);
int	redirect(t_cmd *cmd);
int	heredoc(t_cmd *cmd);
int	close_unused_fd(t_cmd *cmd, pid_t pid);

int	get_cmd_path(t_cmd *cmd);
void	trim_cmd_argv(t_cmd *cmd, const char *set, int direction);

int	get_tmp_file_no(void);
char	*get_tmp_file_name(void);
int	delete_tmp_file(void);

#endif
