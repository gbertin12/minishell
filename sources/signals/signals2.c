/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:00:45 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/17 11:07:04 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	sigint_exec(int sig)
{
	if (sig != SIGINT)
		return ;
	g_lretv = 130;
	ft_putchar_fd('\n', 1);
}

void	sigquit_exec(int sig)
{
	if (sig != SIGQUIT)
		return ;
	g_lretv = 131;
	printf("^\\Quit (core dumped)\n");
}
