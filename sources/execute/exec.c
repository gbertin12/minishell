/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/13 13:19:51 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_exec *exec)
{
	if (!exec->path)
	{
		ft_putstr_fd("minishell: ", 2);
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
		if (exec->token->have_in)
			dup2(exec->token->inputfile, 0);
		redir_out(exec->token);
		if (check_path(exec))
			exit(127);
		execve(exec->path, exec->args, exec->env);
		perror("minishell");
		free_all(ms);
		exit (errno);
	}
	return (0);
}

int	exec_middle(char **args, t_exec *exec, t_minishell *ms)
{
	exec->path = make_path(exec, ms);
	if (pipe(exec->token->pipefd))
		perror("minishell ");
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
		execve(exec->path, args, exec->env);
		perror("minishell ");
		free_all(ms);
		exit (errno);
	}
	return (0);
}

int	exec_last(char **args, t_exec *exec, t_minishell *ms)
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
			{
				free_all(ms);
				exit (1);
			}
			if (dup2(exec->token->outputfile, 1) == -1)
				perror("minishell ");
		}
		if (check_path(exec))
			exit(127);
		execve(exec->path, args, exec->env);
		perror("minishell");
		free_all(ms);
		exit (errno);
	}
	return (0);
}
