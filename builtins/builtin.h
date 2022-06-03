/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:41:40 by mher              #+#    #+#             */
/*   Updated: 2022/06/03 17:33:07 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "../utiles/utiles.h"
# include "../struct.h"

int	ft_pwd(void);
int	ft_cd(char *path);
int	ft_env(t_env *env_head);
int	ft_echo(int argc, char *argv[]);
int	ft_exit(t_cmd *cmd, t_env *env_head);
int	ft_unset(int argc, char *argv[], t_env *env_head);
int	ft_export(int argc, char *argv[], t_env *env_head);

//env_utils
int	init_env_list(t_env *cur, char **envp);
t_env	*new_env(char *key_value);
char	*get_env_key(char *key_value);
char	*get_env_value(char *key_value);
t_env	*compare_env_key(t_env *env_head, char *key);
char	*ft_getenv(t_env *env_head, char *key);

char	*ft_getenv(t_env *env_head, char *key);

#endif
