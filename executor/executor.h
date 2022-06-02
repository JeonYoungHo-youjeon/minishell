/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/06/02 14:57:00 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READ 0
# define WRITE 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minishell.h"

int	executor(t_cmd *cmd, t_env *env_head);
int	redirect(t_cmd *cmd);
int	heredoc(t_cmd *cmd);
int	close_unused_fd(t_cmd *cmd, pid_t pid);
char	*get_cmd_path(char *cmd, char **path);
void	trim_cmd_argv(t_cmd *cmd, const char *set, int direction);

int	get_tmp_file_no(void);
char	*get_tmp_file_name(void);

#endif
