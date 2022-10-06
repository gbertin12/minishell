/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/06 14:30:42 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token)
{
	char	*v_print;

	printf("test\n");
	if (count_arg(token->arg_head))
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	v_print = getcwd(NULL, 0);
	if (v_print == NULL)
	{
		strerror(errno);
		return (1);
	}
	if (*v_print)
	{
		ft_putstr_fd(v_print, 1);
		ft_putstr_fd("\n", 1);
	}
	free(v_print);
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
		if (_pwd(token))
		{
			free_all(ms);
			exit(1);
		}
		free_all(ms);
		exit(0);
	}
	return (1);
}
