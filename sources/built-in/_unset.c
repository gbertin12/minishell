/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:50:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 14:56:55 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child(t_token *token, t_minishell *ms)
{
	init_execute(token, ms);
	redir_out(token);
	if (_unset(token->arg_head, ms))
		exit_child(1, ms);
	else
		exit_child(0, ms);
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

int	exec_unset(t_token *token, t_minishell *ms)
{
	if (count_token(ms->t_head) > 1)
		exec_in_child(token, ms);
	else
	{
		if (init_exec_no_child(token) == 130)
			return (130);
		if (init_exec_no_child(token) == -1)
			return (0);
		if (init_exec_no_child(token) == 1)
			return (1);
		if (_unset(token->arg_head, ms))
			return (1);
		else
			return (0);
	}
	return (0);
}
