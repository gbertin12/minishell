/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/25 18:00:18 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_minishell *ms)
{
	if (getcwd(NULL, 0) == NULL)
	{
		perror("pwd: error retrieving current directory:\
 getcwd: cannot access parent directories");
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
		init_execute(token, ms);
		redir_out(token);
		if (_pwd(ms))
			exit_child(1, ms);
		exit_child(0, ms);
	}
	return (1);
}
