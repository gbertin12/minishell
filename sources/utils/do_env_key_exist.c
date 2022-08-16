/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env_key_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:44:00 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/16 11:10:53 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	do_env_key_exist(char *key, t_minishell *ms)
{
	t_env	*env;

	env = ms->e_head;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
