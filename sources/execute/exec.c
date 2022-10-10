/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:41:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 08:31:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_exec *exec, t_minishell *ms)
{
	if (ft_strchr(exec->token->cmd, '/') || !do_env_key_exist("PATH", ms))
	{
		if (access(exec->token->cmd, 0) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->token->cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	if (!exec->path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->token->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static int	null_cmd(t_exec *exec, t_minishell *ms)
{
	if (!exec->token->cmd || exec->token->cmd[0] == '\0')
	{
		free_all(ms);
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
			exit_child(1, ms);
		if (exec->token->have_in)
			dup2(exec->token->inputfile, 0);
		redir_out(exec->token);
		if (null_cmd(exec, ms))
			exit_child(0, ms);
		if (check_path(exec, ms))
			exit_child(127, ms);
		execve(exec->path, exec->args, exec->env);
		print_err_cmd(exec->token->cmd);
		exit_child(126, ms);
	}
	return (0);
}

int	exec_middle(char **args, t_exec *exec, t_minishell *ms)
{
	exec->path = make_path(exec, ms);
	if (pipe(exec->token->pipefd))
		perror("minishell");
	exec->token->pid = fork();
	if (exec->token->pid < 0)
		return (1);
	if (exec->token->pid == 0)
	{
		if (init_execute(exec->token))
			return (1);
		redir_in(exec->token, exec->last);
		redir_out(exec->token);
		if (null_cmd(exec, ms))
			exit_child(0, ms);
		if (check_path(exec, ms))
			exit_child(127, ms);
		execve(exec->path, args, exec->env);
		print_err_cmd(exec->token->cmd);
		exit_child(126, ms);
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
		if (null_cmd(exec, ms))
			exit_child(0, ms);
		if (exec->token->have_out)
		{
			if (exec->token->outputfile == -1)
				exit_child(1, ms);
			dup2(exec->token->outputfile, 1);
		}
		if (check_path(exec, ms))
			exit_child(127, ms);
		execve(exec->path, args, exec->env);
		print_err_cmd(exec->token->cmd);
		exit_child(126, ms);
	}
	return (0);
}
