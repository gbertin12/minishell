/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_key_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:09:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 15:10:25 by gbertin          ###   ########.fr       */
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
	e_tmp->key = key;
	e_tmp->value = value;
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
