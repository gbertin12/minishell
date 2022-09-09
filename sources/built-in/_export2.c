/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:50:58 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/08 17:04:57 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_append_export(char *export)
{
	int	i;

	i = 0;
	while (export[i] != '\0' && export[i] != '=')
	{
		if (export[i] == '+' && export[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_env	*get_node_env(char *key, t_minishell *ms)
{
	t_env	*node;

	node = ms->e_head;
	while (node)
	{
		if (ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	append_export(t_arg *arg, t_minishell *ms)
{
	char	*key;
	char	*value;
	int		len_key;
	t_env	*env_node;

	len_key = 0;
	while (arg->value[len_key] != '+')
		len_key++;
	key = ft_malloc(sizeof(char) * len_key + 1, ms);
	ft_strlcpy(key, arg->value, len_key + 1);
	if (check_key_env(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg->value, 2);
		ft_putstr_fd("\" not a valid identifier\n", 2);
		return (1);
	}
	if (arg->value[len_key + 2])
		value = ft_split(arg->value, '=', ms)[1];
	else
		value = NULL;
	env_node = get_node_env(key, ms);
	if (env_node != NULL)
	{
		if (env_node->value != NULL)
		{
			if (value != NULL)
				env_node->value = ft_strjoin(env_node->value, value, ms);
		}
		else if (value != NULL)
			env_node->value = value;
	}
	else
		modify_env(key, value, ms);
	return (0);
}