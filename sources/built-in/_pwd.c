/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/06 15:28:27 by ccambium         ###   ########.fr       */
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
	if (token->pid == 0)
	{
		if (init_execute(token))
		{
			free_all(ms);
			exit (1);
		}
		redir_out(token);
		if (_pwd(token, ms))
		{
			free_all(ms);
			exit(1);
		}
		free_all(ms);
		exit(0);
	}
	return (1);
}
