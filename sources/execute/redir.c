/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:44:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/07 09:07:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_token *token)
{
	if (token->have_out)
		dup2(token->outputfile, 1);
	else if (token->next)
	{
		close(token->pipefd[0]);
		dup2(token->pipefd[1], 1);
	}
	return (0);
}

int	redir_in(t_token *token, t_token *last)
{
	if (last->cmd == NULL)
		return (0);
	if (token->have_in == 1)
	{
		if (last->pipefd[0])
			close(last->pipefd[0]);
		if (last->pipefd[1])
			close(last->pipefd[1]);
		dup2(token->inputfile, 0);
	}
	else
	{
		close(last->pipefd[1]);
		dup2(last->pipefd[0], 0);
	}
	return (0);
}
