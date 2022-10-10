/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:14:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 14:36:32 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_too_many(t_token *token, t_minishell *ms)
{
	if (count_arg(token->arg_head) > 1)
	{
		ms->l_retv = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static void	exec_child(t_token *token, t_minishell *ms)
{
	int	ret_v;

	if (init_execute(token))
		exit_child(1, ms);
	redir_out(token);
	if (token->arg_head)
	{
		if (!check_arg(token, ms))
		{
			ret_v = ms->l_retv;
			if (token->arg_head)
			{
				if (check_too_many(token, ms))
					return ;
				if (!check_arg(token, ms))
					ret_v = ft_atoll(token->arg_head->value) % 256;
				else
					ret_v = ms->l_retv;
			}
			free_all(ms);
			exit (ret_v);
		}
	}
}

static int	exec_in_child(t_token *token, t_minishell *ms)
{
	int	ret_v;

	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		exec_child(token, ms);
		ret_v = ms->l_retv;
		exit_child(ret_v, ms);
	}
	return (1);
}

int	b_exit(t_token *token, t_minishell *ms)
{
	int	ret_v;

	if (count_token(ms->t_head) > 1)
		exec_in_child(token, ms);
	else
	{
		ret_v = ms->l_retv;
		printf("exit\n");
		if (token->arg_head)
		{
			if (check_too_many(token, ms))
				return (1);
			if (!check_arg(token, ms))
				ret_v = ft_atoll(token->arg_head->value) % 256;
			else
				ret_v = ms->l_retv;
		}
		rl_clear_history();
		exit_child(ret_v, ms);
	}
	return (0);
}
