/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:50:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 03:49:42 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_elem(t_env *before, t_env *after, t_env *head)
{
	if (!before && !after)
		head->next = NULL;
	if (!before)
		head->next = after;
	else if (after == NULL)
		before->next = NULL;
	else
		before->next = after;
}

int	_unset(char *key, t_minishell *ms)
{
	t_env	*e_env;
	t_env	*e_before;

	e_before = NULL;
	e_env = ms->e_head;
	if (!e_env)
		return (0);
	if (!do_env_key_exist(key, ms))
		return (0);
	while (e_env)
	{
		if (!ft_strncmp(key, e_env->key, ft_strlen(key)))
		{
			unset_elem(e_before, e_env->next, ms->e_head);
			ft_free(e_env->key, ms);
			ft_free(e_env->value, ms);
			return (1);
		}
		e_before = e_env;
		e_env = e_env->next;
	}
	return (0);
}
