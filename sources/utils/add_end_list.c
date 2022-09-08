/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_end_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:08:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/08 11:53:43 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_end_obj(t_obj *head, t_obj *obj)
{
	t_obj	*x;

	x = head;
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}

void	add_end_token(t_token *obj, t_minishell *ms)
{
	t_token	*x;

	x = ms->t_head;
	if (x == NULL)
	{
		ms->t_head = obj;
		return ;
	}
	else
	{
		while (x->next != NULL)
			x = x->next;
		x->next = obj;
	}
}

void	add_end_arg(t_arg *head, t_arg *obj)
{
	t_arg	*x;

	x = head;
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}

void	add_end_file(t_token *token, t_file *obj)
{
	t_file	*x;

	x = token->file_head;
	if (x == NULL)
	{
		token->file_head = obj;
		return ;
	}
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}

void	add_end_err(t_file_error *head, t_file_error *obj)
{
	t_file_error	*x;

	x = head;
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}
