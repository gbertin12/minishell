/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 17:19:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

static void	init(t_minishell *ms, char **envp, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	init_minishell(ms);
	copy_env(ms, envp);
	init_signals();
}

static void reset(t_minishell *ms, char *s)
{
	free_tokens(ms);
	ms->t_head = NULL;
	free(s);
	g_mode = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*s;
	
	init(&ms, envp, argc, argv);
	while (1)
	{
		s = readline("\033[031m┌──\033[034m(\033[032mminishell\033[034m)\n\033[031m└─\033[032m$ \033[034m");
		if (parsing(s, &ms) != 0)
			continue ;
		expand(&ms);
		if (s && *s)
			add_history(s);
		if (ft_strcmp(ms.t_head->cmd, "exit") && count_token(ms.t_head) == 1)
		{
			if (b_exit(ms.t_head, &ms))
			{
				reset(&ms, s);
				continue ;
			}
			break ;
		}
		browse_cmd(&ms);
		reset(&ms, s);
	}
	if (s)
		free(s);
	free_all(&ms);
	return (ms.l_retv);
}
