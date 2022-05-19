/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:37:24 by mher              #+#    #+#             */
/*   Updated: 2022/05/19 18:17:13 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_env(char *envp[])
{
	while (*envp)
	{
		printf("%s\n", *envp);
		++envp;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	ft_env(envp);
	return (0);
}
