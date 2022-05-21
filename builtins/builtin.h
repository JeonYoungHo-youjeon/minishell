/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:41:40 by mher              #+#    #+#             */
/*   Updated: 2022/05/21 17:41:29 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft/include/libft.h"

int	update_envp(const char *key, const char *value);
int	ft_cd(const char *path);
void	ft_env(char *envp[]);
int	ft_pwd(void);
int	ft_echo(int argc, char *args[], char *envp[]);
char	**ft_export(char **envp, char *key_value);

#endif
