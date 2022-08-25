/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:39:59 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/25 14:37:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(t_token *token, t_minishell *ms)
{
	if (token->arg_head)
		return (0);
	if (token->next)
	{
		if (pipe(token->pipefd))
			return (0);
	}
	token->pid = fork();
	if (token->pid == 0)
	{	
		ft_putstr_fd("IN CHILD\n", 2);
		init_execute(token, ms);
		redir_out(token);
		_env(ms);
		exit(0);
	}
	return (1);
}

int check_is_built_in(t_token *token, t_minishell *ms)
{
	if (ft_strcmp(token->cmd, "env"))
		return (exec_env(token, ms));
	return (0);
}