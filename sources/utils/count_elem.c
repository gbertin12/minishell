/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:04:14 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/15 18:14:35 by ccambium         ###   ########.fr       */
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
