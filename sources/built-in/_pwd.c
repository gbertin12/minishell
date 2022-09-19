/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/19 12:29:54 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token)
{
	char	v_print[1000];

	if (count_arg(token->arg_head))
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(v_print, 50) == NULL)
	{
		strerror(errno);
		return (1);
	}
	if (*v_print)
	{
		ft_putstr_fd(v_print, 1);
		ft_putstr_fd("\n", 1);
	}
	return (EXIT_SUCCESS);
}

int	exec_pwd(t_token *token)
{
	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		init_execute(token);
		redir_out(token);
		if (_pwd(token))
			exit(1);
		exit(0);
	}
	return (1);
}
