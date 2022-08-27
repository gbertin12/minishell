/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:36:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/27 14:21:06 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key, t_minishell *ms)
{
	t_env	*env;

	if (!key)
		return (NULL);
	if (!ft_strncmp(key, "?", ft_strlen(key)))
		return (ft_itoa(ms->l_retv, ms));
	if (!do_env_key_exist(key, ms))
		return (NULL);
	env = ms->e_head;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			return (ft_strdup(env->value, ms));
		env = env->next;
	}
	return (NULL);
}
