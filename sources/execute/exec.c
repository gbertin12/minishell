/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 09:56:55 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_first_cmd(t_exec *exec, t_minishell *ms)
{
	t_token	*token;

	token = exec->token;
	exec->path = make_path(exec, ms);
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		if (init_execute(exec->token, ms))
			return (1);
		if (exec->token->have_in)
		{
			if (dup2(exec->token->inputfile, 0) == -1)
				perror("minishell ");
		}
		redir_out(exec->token);
		if (exec->path)
			execve(exec->path, exec->args, exec->env);
		perror("minishell ");
		exit (127);
	}
	return (0);
}

int	exec_middle(char **args, t_exec *exec, t_minishell *ms)
{
	char	*path;

	path = make_path(exec, ms);
	if (pipe(exec->token->pipefd))
		perror("minishell ");
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		if (init_execute(exec->token, ms))
			return (1);
		redir_in(exec->token, exec->last);
		redir_out(exec->token);
		if (path)
			execve(path, args, exec->env);
		perror("minishell ");
		exit (127);
	}
	return (0);
}

int	exec_last(char **args, t_exec *exec, t_minishell *ms)
{
	char	*path;

	path = make_path(exec, ms);
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		init_execute(exec->token, ms);
		redir_in(exec->token, exec->last);
		if (exec->token->have_out)
		{
			if (dup2(exec->token->outputfile, 1) == -1)
				perror("minishell ");
		}
		if (path)
			execve(path, args, exec->env);
		perror("minishell ");
		exit (127);
	}
	return (0);
}
