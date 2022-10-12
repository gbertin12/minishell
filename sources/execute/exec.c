/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 09:20:21 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	null_cmd(t_exec *exec)
{
	if (!exec->token->cmd || exec->token->cmd[0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->token->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static void	check_exec_cmd(t_exec *exec, t_minishell *ms)
{
	if (null_cmd(exec))
		exit_child(0, ms);
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
		if (init_execute(exec->token))
			exit_child(1, ms);
		if (exec->token->have_in)
		{
			if (dup2(exec->token->inputfile, 0) == -1)
			{
				perror("minishell1");
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
		perror("minishell2");
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		if (init_execute(exec->token))
			return (1);
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
		init_execute(exec->token);
		redir_in(exec->token, exec->last);
		if (exec->token->have_out)
		{
			if (exec->token->outputfile == -1)
				exit_child(1, ms);
			if (dup2(exec->token->outputfile, 1) == -1)
			{
				perror("minishell3");
				exit_child(1, ms);
			}
		}
		check_exec_cmd(exec, ms);
	}
	return (0);
}
