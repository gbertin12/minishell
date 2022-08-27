/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:39:59 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 13:45:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(t_token *token, t_minishell *ms)
{
	if (token->arg_head)
		return (1);
	if (token->next)
	{
		if (pipe(token->pipefd))
		{
			perror("");
			return (1);
		}
	}
	token->pid = fork();
	if (token->pid == 0)
	{	
		ft_putstr_fd("IN CHILD\n", 2);
		init_execute(token, ms);
		redir_out(token);
		if (_env(ms))
			exit(1);
		exit(0);
	}
	return (1);
}

int	exec_pwd(t_token *token, t_minishell *ms)
{
	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		init_execute(token, ms);
		redir_out(token);
		if (_pwd(token))
			exit(1);
		exit(0);
	}
	return (1);
}

int	exec_cd(t_token *token, t_minishell *ms)
{
	if (count_token(ms->t_head) == 1)
	{
		if (_cd(token, ms))
			return (0);
	}
	return (1);
}

int	exec_echo(t_token *token, t_minishell *ms)
{
	if (token->next)
	{
		if (pipe(token->pipefd))
			return (0);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		init_execute(token, ms);
		redir_out(token);
		if (_echo(token))
			exit(1);
		exit(0);
	}
	return (1);
}

int	exec_export(t_token *token, t_minishell *ms)
{
	if (_export(token, ms))
	{
		ms->l_retv = 1;
		return (1);
	}
	ms->l_retv = 0;
	return (1);
}

int	exec_unset(t_token *token, t_minishell *ms)
{
	if (_unset(token->arg_head->value, ms))
	{
		ms->l_retv = 1;
		return (1);
	}
	ms->l_retv = 0;
	return (0);
}

int	check_is_built_in(t_token *token, t_minishell *ms)
{
	if (ft_strcmp(token->cmd, "env"))
		return (exec_env(token, ms));
	if (ft_strcmp(token->cmd, "pwd"))
		return (exec_pwd(token, ms));
	if (ft_strcmp(token->cmd, "cd"))
		return (exec_cd(token, ms));
	if (ft_strcmp(token->cmd, "echo"))
		return (exec_echo(token, ms));
	if (ft_strcmp(token->cmd, "export"))
		return (exec_export(token, ms));
	if (ft_strcmp(token->cmd, "unset"))
		return (exec_unset(token, ms));
	return (0);
}
