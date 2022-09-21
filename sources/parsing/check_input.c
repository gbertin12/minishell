/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:43 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/20 14:30:19 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_file(t_file *f)
{
	if (f->next->type)
	{
		if (f->next->append)
			create_error("syntax error near unexpected token `>>'");
		else
			create_error("syntax error near unexpected token `>'");
	}
	else
	{
		if (f->next->append)
			create_error("syntax error near unexpected token `<<'");
		else
			create_error("syntax error near unexpected token `<'");
	}
}

static char	check_file(t_file *head)
{
	t_file	*f;

	f = head;
	while (f)
	{
		if (!f->path || !*f->path)
		{
			if (f->next)
				error_file(f);
			else
				create_error("syntax error near unexpected token `|'");
			return (1);
		}
		f = f->next;
	}
	return (0);
}

static char	check_token(t_token *t, t_token *head)
{
	if (token_is_empty(t))
	{
		if (count_token(head) == 1)
			return (1);
		if (t->next)
			create_error("syntax error near unexpected token `|'");
		else
			create_error("syntax error near unexpected token `newline'");
		return (1);
	}
	if (check_file(t->file_head))
		return (1);
	return (0);
}

char	check_input(t_token *head)
{
	t_token	*t;

	t = head;
	while (t)
	{
		if (check_token(t, head))
			return (1);
		t = t->next;
	}
	return (0);
}
