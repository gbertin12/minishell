/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/17 11:11:26 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	g_lretv = 0;

static void	init(t_minishell *ms, char **envp, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	ft_memset(ms, 0, sizeof(t_minishell));
	if (tcgetattr(0, &ms->term) == -1)
		exit(1);
	ms->term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &ms->term))
		exit(1);
	ms->pwd = get_pwd(ms);
	copy_env(ms, envp);
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
	if (*s && !onlyspace(s))
		add_history(s);
	else
	{
		free(s);
		return ;
	}
	if (parsing(s, ms) != 0)
	{
		g_lretv = 2;
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
		init_signals();
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
	ms.term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &ms.term))
		exit(g_lretv);
	return (g_lretv);
}
