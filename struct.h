/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:09:22 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 14:05:51 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

int g_exit_code;

typedef struct			s_cmd
{
	char			**argv;
	int			argc;
	bool			is_pipe;
	int			fd[2];
	int			infile;
	int			outfile;
	char			*cmd_path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}						t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

#endif
