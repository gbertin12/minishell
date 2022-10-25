/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:05:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/25 14:40:31 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_exec_no_child(t_token *token)
{
	if (token->have_in)
	{
		if (token->inputfile == -2)
			return (130);
		if (token->inputfile == -3)
			return (-1);
		if (token->inputfile < 0)
			return (1);
	}
	if (token->have_out)
	{
		if (token->outputfile < 0)
			return (1);
	}
	return (0);
}

int	init_execute(t_token *token, t_minishell *ms)
{
	if (token->have_in)
	{
		if (token->inputfile == -2)
			exit_child(130, ms);
		if (token->inputfile == -3)
			exit_child(0, ms);
		if (token->inputfile < 0)
			exit_child(1, ms);
	}
	if (token->have_out)
	{
		if (token->outputfile < 0)
			exit_child(1, ms);
	}
	return (0);
}

int	null_cmd(t_exec *exec, t_minishell *ms)
{
	if (exec->token->cmd == NULL || exec->token->cmd[0] == '\0')
	{
		if (exec->token->cmd != NULL && exec->token->cmd[0] == '\0')
		{
			ft_putstr_fd("minishell: : command not found\n", 2);
			return (0);
		}
		exec->token->pid = fork();
		if (exec->token->pid == 0)
			exit_child(g_lretv, ms);
		return (0);
	}
	return (1);
}
