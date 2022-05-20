/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/20 18:23:10 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"

int	ft_pwd(void);
int	ft_cd(const char *path);
void	ft_env(char *envp[]);
int	ft_pwd(void);

void	cd_test(void)
{
	ft_pwd();
	ft_cd("..");
	ft_pwd();
}

void	env_test(char *envp[])
{
	ft_env(envp);
}

void	pwd_test(void)
{
	ft_pwd();
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	cd_test();
	return (0);
}
