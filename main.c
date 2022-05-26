/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:25:10 by youjeon           #+#    #+#             */
/*   Updated: 2022/05/26 14:15:42 by youjeon          ###   ########.fr       */
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

char		*ft_strdup(const char *src)
{
	char	*str;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (src[size] != '\0')
		size++;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t			ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (size == 1 || src[0] == '\0')
		dest[0] = '\0';
	else if (size == 0)
		j = 0;
	else
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		if (i < size)
			dest[i] = '\0';
	}
	while (src[j] != 0)
		j++;
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = 1; // FIXME: 1글자씩 가져오는 함수를 따로 파야할듯?
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	return (ret);
}

void	test_parse(char *line)
{
	char	*str;
	int		quotes;
	int		index;
	int		space;

	str = NULL;
	quotes = 0;
	index = 0;
	space = 0;
	
	while (*line)
	{
		if (*line == '\'')
		{
			if (quotes == 1)
				quotes = -1;
			else if (quotes == 2)
				;
			else
				quotes = 1;
		}
		else if (*line == '\"')
		{
			if (quotes == 2)
				quotes = -1;
			else if (quotes == 1)
				;
			else
				quotes = 2;
		}

		if ((*line == ' ' || *line == ';' || *line == '|') && space == 0 && quotes == 0)
		{
			printf("[%d] : %s\n", index, str);
			free(str);
			str = NULL;
			space = 1;
			index++;
		}
		else if ((*line == '\'' || *line == '\"') && quotes == -1 && space == 0)
		{
			str = ft_strjoin(str, &line[0]);
			printf("[%d] : %s\n", index, str);
			free(str);
			str = NULL;
			space = 1;
			quotes = 0;
			index++;
		}
		else
		{
			if (*line == ' ' && space == 1)
			{
				;
			}
			else if (str == NULL)
			{
				str = (char *)malloc(2 * sizeof(char));
				str[0] = *line;
				str[1] = '\0';
				space = 0;
			}
			else
			{
				str = ft_strjoin(str, &line[0]);
			}
			
		}
		line++;
	}
	if (str != NULL)
	{
		printf("[%d] : %s\n", index, str);
		free(str);
	}
	
	
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
    char			*line;
	t_cmd			*cmd;

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
		
		test_parse(line); // 입력받은 문자열을 그대로 공백, 문자열, 세미콜론, 파이프로 나눠서 출력하면서 감잡기

		if (!is_whitespace(line)) // 입력받은 문자가 있을때만 동작 
		{
			parse(line, &cmd); // 입력받은 문자열을 링크드 리스트에 저장
			test_print_cmd(&cmd); 

			replace(&cmd, envp); // 실행전에 $, \, ~ 등 필요한 부분 replace
			test_print_cmd(&cmd);

			// exec(&cmd, envp) // 완성된 cmd를 실행부에 전달			
		}
		// 파싱 완료한다음 '반드시' free 해줘야함
		free(line);
	}
	
}