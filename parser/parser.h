/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:46:48 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 16:37:55 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include "../struct/struct.h"
# include "../utiles/utiles.h"
# include "../builtins/builtin.h"

char	**ft_split_argc(char const *s, char c, int *argc);
char	*ft_strjoin_char(char *s1, char s2);
int		parse_set_quotes(char line, int quotes);
void	parse(char *line, t_cmd *cmd);
void	replace(t_cmd *cmd, t_env *head);
void	set_signal(int sig_int, int sig_quit);

#endif