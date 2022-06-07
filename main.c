/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:25:10 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/07 19:53:52 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	signal_handler(int signo)
{
	// TODO: 시그널에 따른 종료상태 crtl-c : 130 crtl-\ : 131
	// ctrl-C : 새로운 줄에 새로운 프롬프트 출력
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// ctrl-\ : 아무런 동작을 하지 않음
	// TODO: 자식 프로세스 있을때 작업을 이후에 추가해야함 cat 이랑 cat /dev/urandom 으로 테스트해볼것
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}

}

int			ft_strlen_int(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	s1_len = ft_strlen_int(s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2);
	free(s1);
	return (ret);
}

int	parse_set_quotes(char line, int quotes)
{
	int	result;

	result = quotes;
	if (line == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (line == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}



void	test_parse(char *line)
{
	char	*str = NULL;
	int		quotes = 0;
	int		index = 0;
	int		space = 1;
	int		pipe = 0;
	// 제출 안할 함수여서 구분을 위해 여기서 초기화

	while (*line)
	{
		quotes = parse_set_quotes(*line, quotes); // line 이 \' 혹은 \" 일때 예외 처리를 위해 구분

		if (*line == ' ' && space == 0 && quotes == 0)
		{
			printf("[%d] : %s\n", index, str);
			str = ft_free(str);
			space = 1;
			index++;
		}
		else if (*line == '|' && quotes == 0)
		{
			if (space == 0) //공백이 아닐때만 구조체에 넣고 free
			{
				printf("[%d] : %s\n", index, str);
				str = ft_free(str);
			}
			if (pipe == 1) // 기존 값이 파이프일때(파이프가 연속으로 나왔을때) 예외처리
			{
			}
			// 이 자리에 현재 구조체의 is_pipe를 true로 바꾸고 다음 리스트로 넘어가는 동작 넣을 예정
			index = 0;
			space = 1;
			pipe = 1;
		}
		else
		{
			// 특수문자 예외처리
			if ((*line == ';' || *line == '\\') && quotes == 0)
			{
			}
			// 연달아서 공백이 나오는 경우 예외처리
			if (!(*line == ' ' && space == 1) && quotes == 0)
			{
				str = ft_strjoin_char(str, line[0]);
				space = 0;
				pipe = 0;
			}
		}
		line++;
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
	{
		exit_with_err("quotes error", NULL, 1);
	}
	if (str != NULL) // 마지막에 출력하지 않은 문자열이 남은 경우 처리
	{
		printf("[%d] : %s\n", index, str);
		str = ft_free(str);
	}
}

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

t_cmd	*ft_list_init(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->argc = 0;
	new_mem->argv = NULL;
	new_mem->fd[0] = 0;
	new_mem->fd[1] = 0;
	new_mem->is_pipe = false;
	new_mem->next = NULL;
	new_mem->prev = NULL;
	return (new_mem);
}

static int	get_word_cnt(char const *str, char c)
{
	size_t	count;
	int		chker;

	count = 0;
	chker = 1;
	while (*str != '\0' && *str == c)
		str++;
	while (*str)
	{
		if (chker == 1 && *str != c)
		{
			count++;
			chker = 0;
		}
		if (*str == c)
			chker = 1;
		str++;
	}
	return (count);
}

static void		*is_free(char **str, int str_index)
{
	int	i;

	i = 0;
	while (i < str_index)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char		**set_worddup(char const *s, char c, char **mem)
{
	size_t	word_length;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		word_length = 0;
		while (s[word_length] && s[word_length] != c)
			word_length++;
		if (!(mem[i] = (char *)malloc(sizeof(char) * (word_length + 1))))
			return (is_free(mem, i));
		ft_strlcpy(mem[i], s, word_length + 1);
		s = s + word_length;
		i++;
	}
	mem[i] = NULL;
	return (mem);
}

char			**ft_split_argc(char const *s, char c, int *argc)
{
	char	**new_mem;

	new_mem = NULL;
	if (!s)
		return (NULL);
	*argc = get_word_cnt(s, c);
	if (!(new_mem = (char **)malloc(sizeof(char *) * (*argc + 1))))
		return (NULL);
	new_mem = set_worddup(s, c, new_mem);
	return (new_mem);
}


void	parse(char *line, t_cmd *cmd)
{
	t_cmd	*next;
	char	*str;
	int		quotes;
	int		pipe;

	str = NULL;
	quotes = 0;
	pipe = 0;
	while (*line)
	{
		quotes = parse_set_quotes(*line, quotes); // line 이 \' 혹은 \" 일때 예외 처리를 위해 구분
		if (*line == '|' && quotes == 0)
		{
			if (pipe == 1) // 기존 값이 파이프일때(파이프가 연속으로 나왔을때) 예외처리
				exit_with_err("argv error", "||", 1);;
			// 현재 구조체에 값을 입력하고 다음 리스트로 넘어감
			cmd->is_pipe = true;
			cmd->argv = ft_split_argc(str, ' ', &(cmd->argc));
			next = ft_list_init();
			cmd->next = next;
			next->prev = cmd;
			cmd = next;
			str = ft_free(str);
			pipe = 1;
		}
		else
		{
			// 특수문자 예외처리
			if ((*line == ';' || *line == '\\') && quotes == 0)
				exit_with_err("symbol error", line, 1);
			else if (quotes != 0 && *line == ' ')
			{
				str = ft_strjoin_char(str, -32);
			}
			else
			{
				str = ft_strjoin_char(str, line[0]);
				pipe = 0;
			}
		}
		line++;
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
		exit_with_err("quotes error", NULL, 1);
	if (str != NULL) // 마지막에 문자열이 남은 경우 처리
	{
		cmd->argv = ft_split_argc(str, ' ', &(cmd->argc));
		str = ft_free(str);
	}
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

		if (ptr->is_pipe)
		{
			printf("[%d] is_pipe: true\n", index);
		}
		else
		{
			printf("[%d] is_pipe: false\n", index);
		}
		i = 0;
		index++;
		ptr = ptr->next;
	}
}

void	replace(t_cmd *cmd, t_env *head)
{
	int		i;
	int		j;
	int		size;
	char	*new;
	char	*env;
	int		dollar;
	int		quotes;

	new = NULL;
	env = NULL;
	quotes = 0;
	dollar = 0;
	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			j = 0;
			size = ft_strlen(cmd->argv[i]);
			while (j <= size)
			{
				quotes = parse_set_quotes(cmd->argv[i][j], quotes);

				// TODO: 달러표시가 기존 달러표시 뒤에 붙어서 나올때 처리 안되어있음
				if (cmd->argv[i][j] == '$' && quotes != 1 && dollar == 0)
				{
					dollar = 1; // 작은 따옴표가 아닐때 $ 상태에 돌입
				}
				else if (dollar == 1)
				{
					if (ft_isalnum(cmd->argv[i][j])) // TODO: 언더바(_)도 제외
					{
						env = ft_strjoin_char(env, cmd->argv[i][j]); // 특수문자 혹은 띄어쓰기가 아니면 env 문자열에 차곡차곡 저장
						printf("test env : %s\n", env);
					}
					else if (cmd->argv[i][j] == '?' && env == NULL)
					{
						// $? 일때 에러 코드 반환
						env = ft_itoa(g_exit_code);
						new = ft_strjoin(new, env);
						dollar = 0;
					}
					else
					{
						new = ft_strjoin(new, ft_getenv(head, env));
						env = ft_free(env);
						dollar = 0;
					}
				}
				else
				{
					if (cmd->argv[i][j] == -32)
						new = ft_strjoin_char(new, ' ');
					// 따옴표 안에 들어가있지 않은 따옴표는 입력하지않음
					else if (!(cmd->argv[i][j] == '\"' && quotes != 1) && !(cmd->argv[i][j] == '\'' && quotes != 2))
						new = ft_strjoin_char(new, cmd->argv[i][j]);
				}
				j++;
			}
			cmd->argv[i] = ft_free(cmd->argv[i]);
			cmd->argv[i] = new;
			new = NULL;
			i++;
		}
		cmd = cmd->next;
	}
}

void	ft_free_list(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			cmd->argv[i] = ft_free(cmd->argv[i]);
			i++;
		}
		cmd->argv = ft_free(cmd->argv);
		ptr = cmd;
		cmd = cmd->next;
		ptr = ft_free(ptr);
	}

}

// 1차 test
// 평가 시뮬레이션 대로 입력해보고 구조체가 정확히 출력 되는지 확인

// 예외 처리
// 완성 후 생각나는대로 추가

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
    char			*line;
	t_cmd			*cmd;
	t_env			env_head;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126);
	// signal 입력시 나오는 잔향(Echo) 삭제
	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

	// signal handling
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	g_exit_code = 0;
	// make error 해결
	(void)argc;
	(void)argv;

	init_env_list(&env_head, envp);
	// 화면에 minishell $ 출력 및 입력 대기
	while ((line = readline("minishell $ ")))
	{
		if (*line != '\0' && !is_whitespace(line)) // 입력받은 문자가 있을때만 동작
		{
			// if (ft_strcmp(line, "exit") == 0)
			// 	exit(1);
			add_history(line); // 받은 데이터를 히스토리에 저장.

			// test_parse(line); // 입력받은 문자열을 그대로 출력

			cmd = ft_list_init();
			parse(line, cmd); // 입력받은 문자열을 링크드 리스트에 저장
			//test_print_cmd(cmd); // 리스트 내 내용물 출력

			replace(cmd, &env_head); // 실행전에 $, ', " 등 replace
			// test_print_cmd(cmd);  // 리스트 내 내용물 출력

			executor(cmd, &env_head, envp); // 완성된 cmd를 실행부에 전달
			// printf("g_exit_code: %d\n", g_exit_code); //TEST

			ft_free_list(cmd); // 다음 line으로 넘어가기 전에 free
		}

		// 파싱 완료한다음 '반드시' free 해줘야함
		free(line);
	}

}
