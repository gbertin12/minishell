/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:44:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/18 12:46:48 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_token *token)
{
	if (token->have_out)
	{
		if (dup2(token->outputfile, 1) == -1)
		{
			perror("minishell6");
			return (1);
		}
	}
	else if (token->next)
	{
		close(token->pipefd[0]);
		if (dup2(token->pipefd[1], 1) == -1)
		{
			perror ("minishell4");
			return (1);
		}
		close(token->pipefd[0]);
		close(token->pipefd[1]);
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
		if (dup2(token->inputfile, 0) == -1)
		{
			perror("minishell5");
			return (1);
		}
		if (token->inputfile)
			close(token->inputfile);
	}
	else
	{
		close(last->pipefd[1]);
		if (dup2(last->pipefd[0], 0) == -1)
			return (1);
	}
	return (0);
}
