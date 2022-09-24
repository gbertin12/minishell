/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:20:59 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/23 09:32:22 by ccambium         ###   ########.fr       */
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
	rl_replace_line("", 0);
	exit(sig);
}

void	sigint_handler(int sig)
{
	if (g_mode || sig != SIGINT)
	{
		g_mode = 2;
		return ;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (g_mode || sig != SIGQUIT)
		return ;
}
