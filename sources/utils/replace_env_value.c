/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:38:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/19 11:01:51 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_env_value(char *key, char *value, t_minishell *ms)
{
	t_env	*env;

	if (!value)
		return ;
	env = ms->e_head;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			ft_free(env->value, ms);
			env->value = ft_strdup(value, ms);
			ft_free(env->key, ms);
			env->key = ft_strdup(key, ms);
			if (env->show == 1)
				env->show = 0;
			return ;
		}
		env = env->next;
	}
}
