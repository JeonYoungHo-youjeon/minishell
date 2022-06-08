/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:47:51 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/08 16:25:39 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == (int)*SIG_IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == (int)*SIG_DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_int == 0)
		signal(SIGINT, signal_handler);
	if (sig_quit == (int)*SIG_IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == (int)*SIG_DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == 0)
		signal(SIGQUIT, signal_handler);
}
