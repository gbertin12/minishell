/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:21:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/03 13:37:45 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_null(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	t_arg	*last;

	arg = token->arg_head;
	last = NULL;
	while (arg)
	{
		if (!arg->value || !*arg->value)
		{
			if (!last)
				token->arg_head = arg->next;
			else
				last->next = arg->next;
			free_arg(arg, ms);
			arg = token->arg_head;
			continue ;
		}
		last = arg;
		arg = arg->next;
	}
}
