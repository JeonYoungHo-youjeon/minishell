/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:25:10 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/09 21:21:23 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(0, 0);
	g_exit_code = 0;
	(void)argc;
	(void)argv;
}

void	test_print_cmd(t_cmd *cmd)
{
	int	index = 0;
	int	i = 0;
	t_cmd *ptr;

	ptr = cmd;
	while (ptr)
	{
		printf("[%d] argc: %d\n", index, ptr->argc);
		while (i < ptr->argc)
		{
			printf("[%d] argv[%d]: %s\n", index, i, ptr->argv[i]);
			i++;
		}
		if (ptr->prev)
			printf("[%d] prev: not NULL\n", index);
		else
			printf("[%d] prev: NULL\n", index);
		if (ptr->next)
			printf("[%d] next: not NULL\n", index);
		else
			printf("[%d] next: NULL\n", index);
		if (ptr->is_pipe)
			printf("[%d] is_pipe: true\n", index);
		else
			printf("[%d] is_pipe: false\n", index);
		i = 0;
		index++;
		ptr = ptr->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_cmd			*cmd;
	t_env			env_head;

	main_init(argc, argv);
	init_env_list(&env_head, envp);
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != '\0' && !is_whitespace(line))
		{
			add_history(line);
			cmd = ft_list_init();
			parse(line, cmd);
			replace(cmd, &env_head);
			//test_print_cmd(cmd);
			argc_checker(&cmd);
			test_print_cmd(cmd);
			executor(cmd, &env_head, envp);
			ft_free_list(cmd);
		}
		free(line);
		system("leaks minishell"); //
	}
}
