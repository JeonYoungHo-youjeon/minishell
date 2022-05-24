/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:25:10 by youjeon           #+#    #+#             */
/*   Updated: 2022/05/24 00:25:10 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	// ctrl-C : 새로운 줄에 새로운 프롬프트 출력
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// ctrl-\ : 아무런 동작을 하지 않음
	// 자식 프로세스 있을때 작업을 이후에 추가해야함
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	
}

int	main()
{
	struct termios	term;
    char			*line;

	// signal 입력시 나오는 잔향(Echo) 삭제
	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

	// signal handling
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler); 
	
	// 화면에 minishell $ 출력 및 입력 대기
	while ((line = readline("minishell $ "))) 
	{
		// 받은 데이터를 히스토리에 저장. 
		add_history(line);
		// TODO: 파싱 부분만 만들면 됨
		
		// 파싱 완료한다음 '반드시' free 해줘야함
		free(line);
	}
	
}