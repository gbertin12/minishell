/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:16:24 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/22 13:56:41 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_flag(char	*s)
{
	size_t	i;

	if (!s || s[0] != '-' || !s[0])
		return (0);
	i = 0;
	while (s[++i])
		if (s[i] != 'n')
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
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		if (init_execute(token))
		{
			free_all(ms);
			exit(1);
		}
		redir_out(token);
		if (_echo(token))
		{
			free_all(ms);
			exit(1);
		}
		free_all(ms);
		exit(0);
	}
	return (1);
}
