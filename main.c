/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:25:10 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 16:00:46 by youjeon          ###   ########.fr       */
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
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	g_exit_code = 0;
	(void)argc;
	(void)argv;
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
		if (*line != '\0' && !is_whitespace(line)) // 입력받은 문자가 있을때만 동작
		{
			add_history(line); // 받은 데이터를 히스토리에 저장.
			cmd = ft_list_init();
			parse(line, cmd); // 입력받은 문자열을 링크드 리스트에 저장
			replace(cmd, &env_head); // 실행전에 $, ', " 등 replace
			executor(cmd, &env_head, envp); // 완성된 cmd를 실행부에 전달
			ft_free_list(cmd); // 다음 line으로 넘어가기 전에 free
		}
		free(line);
	}
}
