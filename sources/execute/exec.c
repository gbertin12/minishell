/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/06 15:10:54 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_exec *exec)
{
	if (!exec->path)
	{
		ft_putstr_fd("minishell1: ", 2);
		ft_putstr_fd(exec->token->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
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
			exit (1);
		if (exec->token->have_in && exec->token->cmd)
		{
			if (dup2(exec->token->inputfile, 0) == -1)
				perror("minishell2 ");
		}
		redir_out(exec->token);
		if (check_path(exec))
			exit(127);
		execve(exec->path, exec->args, exec->env);
		if (exec->token->cmd != NULL)
			perror("minishelll3");
		free_all(ms);
		exit (errno);
	}
	return (0);
}

int	exec_middle(char **args, t_exec *exec, t_minishell *ms)
{
	char	*path;

	path = make_path(exec, ms);
	if (pipe(exec->token->pipefd))
		perror("minishell4 ");
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		if (init_execute(exec->token))
			return (1);
		redir_in(exec->token, exec->last);
		redir_out(exec->token);
		if (check_path(exec))
			exit(127);
		execve(path, args, exec->env);
		perror("minishell5 ");
		free_all(ms);
		exit (errno);
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
		init_execute(exec->token);
		redir_in(exec->token, exec->last);
		if (exec->token->have_out)
		{
			if (dup2(exec->token->outputfile, 1) == -1)
				perror("minishell7");
		}
		if (check_path(exec))
			exit(127);
		execve(path, args, exec->env);
		perror("minishell6");
		free_all(ms);
		exit (errno);
	}
	return (0);
}
