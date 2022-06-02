/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:31:34 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/02 14:54:38 by mher             ###   ########.fr       */
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

# include "./builtins/builtin.h"

extern int g_exit_code;

typedef struct			s_cmd
{
	char			**argv;
	int				argc;
	bool			is_pipe;
	int				fd[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
}						t_cmd;

#endif
