/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:44:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 12:25:44 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_token *token)
{
	if (token->have_out)
	{
		if (dup2(token->outputfile, 1) == -1)
			perror("minishell 6 : ");
	}
	else if (token->next)
	{
		close(token->pipefd[0]);
		if (dup2(token->pipefd[1], 1) == -1)
			perror("minishell 7 : ");
	}
	return (0);
}

int	redir_in(t_token *token, t_token *last)
{
	if (token->have_in == 1)
	{
		if (last->pipefd[0])
			close(last->pipefd[0]);
		if (last->pipefd[1])
			close(last->pipefd[1]);
		if (dup2(token->inputfile, 0))
			perror("minishell 4 : ");
	}
	else
	{
		close(last->pipefd[1]);
		if (dup2(last->pipefd[0], 0))
			perror("minishell 5 : ");
	}
	return (0);
}
