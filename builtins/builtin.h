/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:41:40 by mher              #+#    #+#             */
/*   Updated: 2022/05/24 19:25:49 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft/include/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

int	ft_pwd(void);
int	ft_cd(const char *path);
int	ft_echo(int argc, char *argv[], t_env *env_head);
void	ft_unset(t_env *env_head, char *key);
void	ft_env(t_env *env_head);
int	ft_export(t_env *env_head, char *key, char *value);

//env_utils
int	init_env_list(t_env *cur, char **envp);
char	*get_env_key(char *env);
char	*get_env_value(char *env);
t_env	*compare_env_key(t_env *env_head, char *key);

#endif
