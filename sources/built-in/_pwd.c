/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/11 14:50:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token, t_minishell *ms)
{
	if (count_arg(token->arg_head))
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	ft_putstr_fd(ms->pwd, 1);
	ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}

int	exec_pwd(t_token *token, t_minishell *ms)
{
	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid < 0)
		return (1);
	if (token->pid == 0)
	{
		if (ms->exec->last)
		{
			close(ms->exec->last->pipefd[0]);
			close(ms->exec->last->pipefd[1]);
		}
		if (init_execute(token))
			exit_child(1, ms);
		redir_out(token);
		if (_pwd(token, ms))
			exit_child(1, ms);
		exit_child(0, ms);
	}
	return (1);
}
