/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:44:53 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/11 14:50:31 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_child(t_token *token, t_minishell *ms)
{
	if (init_execute(token))
		exit_child(1, ms);
	redir_out(token);
	if (token->arg_head == NULL)
	{
		if (_export(token, ms))
			exit_child(1, ms);
		exit_child(0, ms);
	}	
	return (0);
}

static int	exec_in_child(t_token *token, t_minishell *ms)
{
	if (pipe(token->pipefd))
	{
		perror("minishell ");
		return (1);
	}
	token->pid = fork();
	if (token->pid == -1)
	{
		perror("minishell ");
		return (1);
	}
	if (ms->exec->last)
	{
		close(ms->exec->last->pipefd[0]);
		close(ms->exec->last->pipefd[1]);
	}
	if (token->pid == 0)
		exec_child(token, ms);
	return (1);
}

static int	exec_in_parent(t_token *token, t_minishell *ms)
{
	if (init_execute(token))
		return (1);
	redir_out(token);
	if (_export(token, ms))
		return (1);
	return (0);
}

int	exec_export(t_token *token, t_minishell *ms)
{
	if (token->next && !token->arg_head)
	{
		exec_in_child(token, ms);
		return (1);
	}
	else
	{
		if (exec_in_parent(token, ms))
			return (1);
		else
			return (0);
	}
	return (0);
}
