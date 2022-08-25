/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:20:59 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/25 16:40:55 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	g_mode;

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sigint_heredoc(int sig)
{
	unlink(".tmp");
	exit(sig);
}

void	sigint_handler(int sig)
{
	if (g_mode || sig != SIGINT)
		return ;
	printf("\n\033[031m┌──\033[034m(\033[032mminishell\033[034m)\n");
	rl_on_new_line();
	rl_replace_line("\n", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (g_mode || sig != SIGQUIT)
		return ;
}
