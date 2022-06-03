/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:09:22 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/04 03:35:19 by mher             ###   ########.fr       */
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
	int			infile_fd;
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
