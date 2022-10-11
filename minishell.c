/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 17:06:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

static void	init(t_minishell *ms, char **envp, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	ft_memset(ms, 0, sizeof(t_minishell));
	ms->pwd = get_pwd(ms);
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
	if (*s)
		add_history(s);
	else
	{
		free(s);
		return ;
	}
	if (parsing(s, ms) != 0)
	{
		ms->l_retv = 2;
		return (reset(ms, s));
	}
	if (expand(ms))
		return (reset(ms, s));
	if (ms->t_head && ft_strcmp(ms->t_head->cmd, "exit")
		&& count_token(ms->t_head) == 1)
	{
		if (b_exit(ms->t_head, ms))
			return (reset(ms, s));
	}
	browse_cmd(ms);
	reset(ms, s);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*prompt;

	init(&ms, envp, argc, argv);
	while (1)
	{
		if (g_mode == 2)
			ms.l_retv = 130;
		g_mode = 0;
		prompt = get_prompt(&ms);
		ms.s = readline(prompt);
		ft_free(prompt, &ms);
		if (!ms.s)
			break ;
		main2(&ms, ms.s);
	}
	reset(&ms, ms.s);
	free_all(&ms);
	rl_clear_history();
	return (ms.l_retv);
}
