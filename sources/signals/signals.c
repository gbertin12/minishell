/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:20:59 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 10:06:20 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sigint_heredoc(int sig)
{
	rl_replace_line("", 0);
	exit(sig);
}

void	exec_signals(void)
{
	signal(SIGINT, sigint_exec);
	signal(SIGQUIT, sigquit_exec);
}

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_lretv = 130;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
}
