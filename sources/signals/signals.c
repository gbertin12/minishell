/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:20:59 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/26 15:54:41 by ccambium         ###   ########.fr       */
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
	char	*pwd;

	if (g_mode || sig != SIGINT)
		return ;
	pwd = getcwd(NULL, 0);
	printf("\n%s┌──%s(%sminishell%s)%s──%s[%s%s%s]\n", BLUE, YELLOW,
		GREEN, YELLOW, BLUE, YELLOW, GREEN, pwd, YELLOW);
	free(pwd);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (g_mode || sig != SIGQUIT)
		return ;
}
