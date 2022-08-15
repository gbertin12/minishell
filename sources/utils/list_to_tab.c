/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:40 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/15 18:42:07 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab(t_minishell *ms)
{
	char	**ret_v;
	char	*s_tmp;
	size_t	nb_element;
	size_t	i;
	t_env	*tmp;

	nb_element = count_env(ms->e_head);
	ret_v = ft_malloc(nb_element + 1, ms);
	if (!ret_v)
		return (ret_v);
	i = -1;
	tmp = ms->e_head;
	while (++i < nb_element)
	{
		s_tmp = ft_strjoin(tmp->key, "=");
		ret_v[i] = ft_strjoin(s_tmp, tmp->value);
		free(s_tmp);
		tmp = tmp->next;
	}
	ret_v[i] = NULL;
	return (ret_v);
}