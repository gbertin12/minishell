/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:56:03 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/12 14:21:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*add_front_arg(t_arg *begin, char *value, t_minishell *ms)
{
	t_arg	*new;
	
	new = ft_malloc(sizeof(t_arg), ms);
	if (!new)
		return (NULL);
	new->value = value;
	new->next = begin;
	return (new);
}