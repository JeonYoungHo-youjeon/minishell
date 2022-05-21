/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:50:33 by mher              #+#    #+#             */
/*   Updated: 2022/05/21 17:51:57 by mher             ###   ########.fr       */
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

void	echo_test(int argc, char *argv[], char *envp[])
{
	ft_echo(argc, argv, envp);
}

char **copy_env(char **envp)
{
	int	i;
	size_t	j;
	int	len;
	char	**ret;
	
	len = 0;
	while (envp[len])
		++len;
	ret = (char **)malloc(len * sizeof(char *) + 1);
	i = 0;
	while (i < len)
	{
		ret[i] = (char *)malloc(ft_strlen(envp[i]) * sizeof(char) + 1);
		j = 0;
		while (j <= ft_strlen(envp[i]))
		{
				ret[j] = envp[j];
				++j;
		}
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

void	exprot_test(char **envp, char *key_value)
{
	char **tmp;
	char **new;

	tmp = copy_env(envp);
	ft_env(tmp);
	new = ft_export(tmp, key_value);
	ft_env(new);
	free(new);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	exprot_test(envp, "TEST=1234");
	return (0);
}
