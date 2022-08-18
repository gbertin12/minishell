/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_end_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:08:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 03:33:23 by ccambium         ###   ########.fr       */
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
