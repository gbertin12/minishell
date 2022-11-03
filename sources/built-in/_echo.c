/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:16:24 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/03 11:08:44 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_flag(char	*s)
{
	size_t	i;

	if (!s || s[0] != '-' || !s[0])
		return (0);
	i = 0;
	if (s[0] == '-' && !s[1])
		return (0);
	while (s[++i])
		if (s[i] != 'n' && i > 1)
			return (0);
	return (1);
}

int	_echo(t_token *token)
{
	t_arg		*arg;
	int			flag;

	flag = 0;
	arg = token->arg_head;
	while (arg)
	{
		if (check_flag(arg->value))
			flag++;
		else
			break ;
		arg = arg->next;
	}
	while (arg)
	{
		printf("%s", arg->value);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	exec_echo(t_token *token, t_minishell *ms)
{
	if (token->next)
	{
		if (pipe(token->pipefd) == -1)
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
		if (_echo(token))
			exit_child(1, ms);
		exit_child(0, ms);
	}
	return (1);
}
