/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:31:02 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/29 13:10:59 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env(t_minishell *ms, char **env)
{
	size_t	i;
	char	**s;
	t_env	*e_tmp;
	t_env	*last;

	i = -1;
	last = NULL;
	if (env == NULL)
		return ;
	while (env[++i])
	{
		e_tmp = ft_malloc(sizeof(t_env), ms);
		if (!e_tmp)
			return ;
		if (ms->e_head == NULL)
			ms->e_head = e_tmp;
		s = ft_split(env[i], '=', ms);
		e_tmp->key = s[0];
		e_tmp->value = ft_superjoin(s, ms);
		ft_free(s, ms);
		if (last != NULL)
			last->next = e_tmp;
		e_tmp->next = NULL;
		last = e_tmp;
	}
}
