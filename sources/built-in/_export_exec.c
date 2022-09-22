/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:44:53 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/22 14:10:58 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_child(t_token *token, t_minishell *ms)
{
	if (init_execute(token))
	{
		free_all(ms);
		exit (1);
	}
	redir_out(token);
	if (token->arg_head == NULL)
	{
		if (_export(token, ms))
		{
			free_all(ms);
			exit (1);
		}
		free_all(ms);
		exit (0);
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
	if (token->pid == 0)
		exec_child(token, ms);
	return (1);
}

static int	exec_in_parent(t_token *token, t_minishell *ms)
{
	if (init_execute(token))
		return (1);
	if (token->have_out)
	{
		if (dup2(token->outputfile, 1))
		{
			perror("minishell ");
			return (1);
		}
		close(token->outputfile);
	}
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
