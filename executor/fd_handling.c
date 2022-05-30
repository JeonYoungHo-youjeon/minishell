/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:22 by mher              #+#    #+#             */
/*   Updated: 2022/05/31 02:56:44 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//execve(cmd_path, cmd->argv, cmd->envp); 를 수행할때 ">", ">>", "<" 등 리다이렉션 문자는 있으면 안되기 때문에 커맨드, 옵션 만 남기고 제거한다.
//direction == 1 인 경우 처음만난 set을 기준으로 오른쪽에 있는 문자열을 제거한다.
//direction == -1 인 경우 처음만난 set을 기준으로 set 포함 왼쪽에 있는 문자열을 제거한다.
void	trim_cmd_argv(t_cmd *cmd, const char *set, int direction)
{
	int	i;
	int	tmp;
	int	argc;

	i = -1;
	argc = cmd->argc;
	while (++i < argc)
		if (ft_strcmp(cmd->argv[i], set) == 0)
			break ; 
	if (direction == 1)
	{
		cmd->argv[i] = 0;
		cmd->argc -= argc - i;
		while (i < argc)
			free(cmd->argv[++i]);
	}
	else if (direction == -1)
	{
		tmp = i;
		while (i >= 0)
			free(cmd->argv[i--]);
		cmd->argv += tmp + 1;
		cmd->argc -= tmp + 1;
	}
}

static int	redirect_pipe(t_cmd *cmd)
{
	// cmd 가 파이프로 입력을 받는 경우
	if (cmd->prev != 0 && cmd->prev->is_pipe) 
		dup2(cmd->prev->fd[READ], STDIN_FILENO);
	// cmd 가 파이프로 출력하는 경우
	if (cmd->is_pipe) 
		dup2(cmd->fd[WRITE], STDOUT_FILENO);
	return (0);
}

static int	redirect_infile(t_cmd *cmd)
{
	int	fd;

	if (ft_strcmp(cmd->argv[0], "<"))
		return (0);
	fd = open(cmd->argv[1], O_RDONLY);
	if (fd == -1)
		perror("file open error");
	dup2(fd, STDIN_FILENO);
	trim_cmd_argv(cmd, cmd->argv[1], -1);
	return (0);
}

static int	redirect_outfile(t_cmd *cmd)
{
	int	i;
	int	fd;
	int	o_flag;

	i = 1;
	fd = -1;
	// "cat infile > a > b > c" 같은 경우 a, b, c 파일모두 생성 되지만 출력은 c 에만 된다.
	// 따라서 while 문을 돌면서 a, b, c 파일모두 생성 해준다.
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
	trim_cmd_argv(cmd, ">", 1);
	trim_cmd_argv(cmd, ">>", 1);
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
