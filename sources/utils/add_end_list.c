/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_end_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:08:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 11:42:58 by gbertin          ###   ########.fr       */
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

void	add_end_token(t_token *head, t_token *obj)
{
	t_token	*x;

	x = head;
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}

void	add_end_arg(t_arg *head, t_arg *obj)
{
	t_arg	*x;

	x = head;
	while (x->next != NULL)
		x = x->next;
	x->next = obj;
}