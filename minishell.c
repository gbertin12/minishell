/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/20 17:52:18 by ccambium         ###   ########.fr       */
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

static void	reset(t_minishell *ms, char *s)
{
	free_tokens(ms);
	ms->t_head = NULL;
	if (s)
		free(s);
	else
		printf("\n");
}

static void	main2(t_minishell *ms, char *s)
{
	if (s && *s)
		add_history(s);
	if (parsing(s, ms) != 0)
	{
		reset(ms, s);
		return ;
	}
	if (expand(ms))
		return ;
	if (ms->t_head && ft_strcmp(ms->t_head->cmd, "exit")
		&& count_token(ms->t_head) == 1)
	{
		if (b_exit(ms->t_head, ms))
		{
			reset(ms, s);
			exit(ms->l_retv);
		}
		exit(ms->l_retv);
	}
	browse_cmd(ms);
	reset(ms, s);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*s;

	init(&ms, envp, argc, argv);
	while (1)
	{
		if (g_mode)
		{
			if (g_mode == 2)
				ms.l_retv = 130;
			g_mode = 0;
		}
		s = readline(get_prompt(&ms));
		if (!s || !s[0])
		{
			if (!s)
				break ;
			reset(&ms, s);
			continue ;
		}
		main2(&ms, s);
	}
	reset(&ms, s);
	free_all(&ms);
	return (ms.l_retv);
}
