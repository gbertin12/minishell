/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:16:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/22 15:25:15 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

static	size_t	count_file(t_file *file_head)
{
	size_t		count;
	t_file		*tmp;

	count = 0;
	tmp = file_head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static	size_t	size_t_ternary(char	condition, size_t a, size_t b)
{
	if (condition)
		return (a);
	return (b);
}

void	print_token(t_token *token)
{
	size_t	i;
	size_t	nb_arg;
	size_t	nb_redir;

	i = 0;
	nb_arg = count_arg(token->arg_head);
	nb_redir = count_file(token->file_head);
}
