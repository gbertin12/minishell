/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:44:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/06 15:26:46 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	print_error()
{
	perror("minishell ");
	return (1);	
}

int	redir_out(t_token *token)
{
	// if (!token->cmd)
	// {
	// 	if (token->pipefd[0])
	// 		close(token->pipefd[0]);
	// 	if (token->pipefd[1])
	// 		close(token->pipefd[1]);
	// 	return (1);
	// }
	if (token->have_out)
	{
		if (dup2(token->outputfile, 1) == -1)
			return (print_error());
	}
	else if (token->next)
	{
		close(token->pipefd[0]);
		if (dup2(token->pipefd[1], 1) == -1)
			return (print_error());
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
			return (print_error());
	}
	else
	{
		// if (!last->cmd)
		// 	return (1);
		close(last->pipefd[1]);
		if (dup2(last->pipefd[0], 0))
			return (print_error());
	}
	return (0);
}
