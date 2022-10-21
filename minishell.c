/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 15:14:17 by ccambium         ###   ########.fr       */
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
	if (tcgetattr(0, &ms->old_term) == -1)
		exit(1);
	if (tcgetattr(0, &ms->term) == -1)
		exit(1);
	ms->term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSANOW, &ms->term))
		exit(1);
	ms->pwd = get_pwd(ms);
	if (!envp[0])
		create_basic_environement(ms);
	else
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
	if (*s)
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
	browse_cmd(ms);
	reset(ms, s);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*prompt;

	if (!isatty(0) || !isatty(1))
		return (EXIT_SUCCESS);
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
	printf("exit");
	reset(&ms, ms.s);
	free_all(&ms);
	rl_clear_history();
	tcsetattr(0, TCSANOW, &ms.old_term);
	return (g_lretv);
}
