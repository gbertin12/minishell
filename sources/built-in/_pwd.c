/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/06 14:13:56 by gbertin          ###   ########.fr       */
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
		printf("%s\n", v_print);
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
