/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 12:12:25 by ccambium         ###   ########.fr       */
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
	if (s)
		free(s);
	else
		printf("\n");
	g_mode = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*s;

	init(&ms, envp, argc, argv);
	while (1)
	{
		if (g_mode == 5)
		{
			ms.l_retv = 130;
			g_mode = 0;
		}
		s = readline(get_prompt(&ms));
		if (!s || !s[0])
		{
			reset(&ms, s);
			continue ;
		}
		if (parsing(s, &ms) != 0)
		{
			reset(&ms, s);
			continue ;
		}
		if (ms.t_head && ms.t_head->arg_head && ms.t_head->file_head)
			printf("cmd = %s\narg = %s\n file = %s\n", ms.t_head->cmd, ms.t_head->arg_head->value, ms.t_head->file_head->path);
		else if (ms.t_head && ms.t_head->arg_head)
			printf("cmd = %s\narg = %s\n", ms.t_head->cmd, ms.t_head->arg_head->value);
		else if (ms.t_head && ms.t_head->file_head)
			printf("cmd = %s\nfile = %s\n", ms.t_head->cmd, ms.t_head->file_head->path);
		else if (ms.t_head)
			printf("cmd = %s\n", ms.t_head->cmd);
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
