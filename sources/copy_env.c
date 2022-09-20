/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:31:02 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/20 17:48:23 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*copy_env2(t_minishell *ms, char **env, size_t i)
{
	t_env	*e_tmp;
	char	**s;

	e_tmp = ft_malloc(sizeof(t_env), ms);
	if (!e_tmp)
		return (NULL);
	if (ms->e_head == NULL)
		ms->e_head = e_tmp;
	s = ft_split(env[i], '=', ms);
	if (!s)
		return (NULL);
	e_tmp->key = s[0];
	e_tmp->value = ft_superjoin(NULL, s, ms);
	ft_free(s, ms);
	return (e_tmp);
}

void	copy_env(t_minishell *ms, char **env)
{
	size_t	i;
	t_env	*e_tmp;
	t_env	*last;

	i = -1;
	last = NULL;
	if (env == NULL)
		return ;
	while (env[++i])
	{
		e_tmp = copy_env2(ms, env, i);
		if (!e_tmp)
			return ;
		if (last != NULL)
			last->next = e_tmp;
		e_tmp->next = NULL;
		last = e_tmp;
	}
}
