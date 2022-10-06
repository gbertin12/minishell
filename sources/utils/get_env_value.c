/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:36:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/02 13:47:46 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key, t_minishell *ms)
{
	t_env	*env;

	if (!key)
		return (NULL);
	if (!ft_strncmp(key, "?", ft_strlen(key) + 1))
		return (ft_itoa(ms->l_retv, ms));
	if (!ft_strncmp(key, "PWD", ft_strlen(key) + 1)
		&& !do_env_key_exist(key, ms))
		return (getcwd(NULL, 0));
	if (!do_env_key_exist(key, ms))
		return (NULL);
	env = ms->e_head;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
			return (ft_strdup(env->value, ms));
		env = env->next;
	}
	return (NULL);
}
