/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:22 by mher              #+#    #+#             */
/*   Updated: 2022/05/30 20:52:47 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	redirect_pipe(t_cmd *cmd)
{
	if (cmd->prev != 0 && cmd->prev->is_pipe) // cmd 가 파이프로 입력을 받는 경우
		dup2(cmd->prev->fd[READ], STDIN_FILENO);
	if (cmd->is_pipe) // cmd 가 파이프로 출력하는 경우
		dup2(cmd->fd[WRITE], STDOUT_FILENO);
	return (0);
}

static int	trim_cmd(t_cmd *cmd, char *set, int direction)
{
	int	i;
	char	**argv;

	i = 0;
	argv = cmd->argv;
	while (i < cmd->argc)
	{
		if (!ft_strcmp(argv[i], ">") || !ft_strcmp(argv[i], ">>"))
			break ;
		++i;
	}
	return (0);
}

static int	redirect_infile(t_cmd *cmd)
{
	int	fd;

	if (ft_strcmp(cmd->argv[0], "<") == 0)
	{
		fd = open(cmd->argv[1], O_RDONLY);
		if (fd == -1)
			perror("file open error");
		dup2(fd, STDIN_FILENO);
		cmd->argv += 2; //argv 시작주소를 옮김
		cmd->argc -= 2; // todo: 이전 주소들 free 해줘야함
	}
	return (0);
}

static int	redirect_outfile(t_cmd *cmd)
{
	int	i;
	int	fd;
	int	o_flag;

	i = 1;
	fd = -1;
	while (i < cmd->argc)
	{
		o_flag = 0;
		if (ft_strcmp(cmd->argv[i], ">") == 0)
			o_flag = O_RDWR | O_CREAT | O_TRUNC;
		else if (ft_strcmp(cmd->argv[i], ">>") == 0)
			o_flag = O_WRONLY | O_CREAT | O_APPEND;
		if (o_flag != 0)
			fd = open(cmd->argv[i + 1] , o_flag, 0644);
		if (o_flag != 0 && i + 2 < cmd->argc) //마지막 ">" 아니라면 생성한 파일 fd를 닫아준다.
			close(fd);
		++i;
	}
	if (fd != -1)
		dup2(fd, STDOUT_FILENO);
	i = 1;
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], ">") == 0 || ft_strcmp(cmd->argv[i], ">>") == 0)
		{
			cmd->argv[i++] = 0;
			while (i < cmd->argc)
			{
				free(cmd->argv[i]);
				++i;
			}
		}
		else
			++i;
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	redirect_pipe(cmd);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	return (0);
}

int	close_unused_fd(t_cmd *cmd, pid_t pid)
{
	if (pid == 0)
		close(cmd->fd[READ]);
	else
		close(cmd->fd[WRITE]);
	return (0);
}
