/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:31:34 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/06 17:37:33 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "./utiles/utiles.h"
# include "./builtins/builtin.h"
# include "./executor/executor.h"
# include "struct.h"

void	parse(char *line, t_cmd *cmd);
void	replace(t_cmd *cmd, t_env *head);

#endif
