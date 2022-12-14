/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_key_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:09:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 13:24:36 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_key_value(char *key, char *value, t_minishell *ms)
{
	t_env	*env;
	t_env	*e_tmp;

	env = ms->e_head;
	e_tmp = ft_malloc(sizeof(t_env), ms);
	if (!e_tmp)
		return ;
	e_tmp->key = ft_strdup(key, ms);
	e_tmp->value = ft_strdup(value, ms);
	e_tmp->next = NULL;
	if (env == NULL)
		ms->e_head = e_tmp;
	else
	{
		while (env->next != NULL)
			env = env->next;
		env->next = e_tmp;
	}
}
