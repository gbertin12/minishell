/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 09:03:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_exec_cmd(t_exec *exec, t_minishell *ms)
{
	if (check_path(exec, ms))
		exit_child(127, ms);
	execve(exec->path, exec->args, exec->env);
	print_err_cmd(exec->token->cmd);
	exit_child(126, ms);
}

int	exec_first_cmd(t_exec *exec, t_minishell *ms)
{
	exec->path = make_path(exec, ms);
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		init_execute(exec->token, ms);
		if (exec->token->have_in)
		{
			if (dup2(exec->token->inputfile, 0) == -1)
			{
				perror("minishell");
				exit_child(1, ms);
			}
			if (exec->token->inputfile)
				close(exec->token->inputfile);
		}
		redir_out(exec->token);
		check_exec_cmd(exec, ms);
	}
	return (0);
}

int	exec_middle(t_exec *exec, t_minishell *ms)
{
	exec->path = make_path(exec, ms);
	if (pipe(exec->token->pipefd) == -1)
		perror("minishell");
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		init_execute(exec->token, ms);
		redir_in(exec->token, exec->last);
		redir_out(exec->token);
		check_exec_cmd(exec, ms);
	}
	return (0);
}

int	exec_last(t_exec *exec, t_minishell *ms)
{
	exec->path = make_path(exec, ms);
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		init_execute(exec->token, ms);
		redir_in(exec->token, exec->last);
		if (exec->token->have_out)
		{
			if (exec->token->outputfile == -1)
				exit_child(1, ms);
			if (dup2(exec->token->outputfile, 1) == -1)
			{
				perror("minishell");
				exit_child(1, ms);
			}
		}
		check_exec_cmd(exec, ms);
	}
	return (0);
}
