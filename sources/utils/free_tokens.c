/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:09:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 23:27:24 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_files(t_file *head, t_minishell *ms)
{
	t_file	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free(tmp->path, ms);
		ft_free(tmp, ms);
	}
}

static void	free_args(t_arg *head, t_minishell *ms)
{
	t_arg	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free(tmp->value, ms);
		ft_free(tmp, ms);
	}
}

void	free_tokens(t_minishell *ms)
{
	t_token	*tmp;
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		free_files(token->file_head, ms);
		free_args(token->arg_head, ms);
		ft_free(token->cmd, ms);
		tmp = token;
		token = token->next;
		ft_free(tmp, ms);
	}
}
