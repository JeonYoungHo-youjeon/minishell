/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:35:59 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 15:57:47 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
