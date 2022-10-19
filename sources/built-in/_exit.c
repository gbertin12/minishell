/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:14:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/19 12:43:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_too_many(t_token *token)
{
	if (count_arg(token->arg_head) > 1)
	{
		g_lretv = 1;
		if (!check_arg(0, token))
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
		if (!check_arg(1, token))
		{
			ret_v = g_lretv;
			if (token->arg_head)
			{
				if (check_too_many(token))
					return ;
				if (!check_arg(1, token))
					ret_v = ft_atoll(token->arg_head->value) % 256;
				else
					ret_v = g_lretv;
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
		if (ms->exec->last)
		{
			close(ms->exec->last->pipefd[0]);
			close(ms->exec->last->pipefd[1]);
		}
		exec_child(token, ms);
		ret_v = g_lretv;
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
		ret_v = g_lretv;
		printf("exit\n");
		if (token->arg_head)
		{
			if (check_too_many(token) && !check_arg(0, token))
				return (1);
			else if (!check_arg(1, token))
				ret_v = ft_atoll(token->arg_head->value) % 256;
			else
				ret_v = g_lretv;
		}
		rl_clear_history();
		tcsetattr(0, TCSANOW, &ms->old_term);
		exit_child(ret_v, ms);
	}
	return (0);
}
