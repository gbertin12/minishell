/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:04:14 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/13 13:28:55 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_env(t_env *ptr)
{
	size_t	ret_v;
	t_env	*tmp;

	if (!ptr)
		return (0);
	ret_v = 0;
	tmp = ptr;
	while (tmp != NULL)
	{
		ret_v++;
		tmp = tmp->next;
	}
	return (ret_v);
}

size_t	count_arg(t_arg *ptr)
{
	size_t	ret_v;
	t_arg	*tmp;

	if (!ptr)
		return (0);
	ret_v = 0;
	tmp = ptr;
	while (tmp != NULL)
	{
		ret_v++;
		tmp = tmp->next;
	}
	return (ret_v);
}

size_t	count_token(t_token *ptr)
{
	size_t	ret_v;
	t_token	*tmp;

	if (!ptr)
		return (0);
	ret_v = 0;
	tmp = ptr;
	while (tmp != NULL)
	{
		ret_v++;
		tmp = tmp->next;
	}
	return (ret_v);
}

size_t	count_file(t_file *ptr)
{
	size_t	ret_v;
	t_file	*tmp;

	if (!ptr)
		return (0);
	ret_v = 0;
	tmp = ptr;
	while (tmp != NULL)
	{
		ret_v++;
		tmp = tmp->next;
	}
	return (ret_v);
}

size_t	count_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		;
	return (i);
}
