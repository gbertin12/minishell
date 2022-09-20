/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:50:58 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/20 17:40:23 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_not_valid_identifier(char *function, char *print)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(print, 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	return (1);
}

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

int	append_export2(char *key, char *value, t_minishell *ms)
{
	t_env	*env_node;

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
	return (1);
}

int	append_export(t_arg *arg, t_minishell *ms)
{
	char	*key;
	char	*value;
	char	**tmp;
	int		len_key;

	len_key = 0;
	while (arg->value[len_key] != '+')
		len_key++;
	key = ft_malloc(sizeof(char) * len_key + 1, ms);
	if (!key)
		return (EXIT_FAILURE);
	ft_strlcpy(key, arg->value, len_key + 1);
	if (check_key_env(key))
		return (print_not_valid_identifier("export3", arg->value));
	if (arg->value[len_key + 2])
	{
		tmp = ft_split(arg->value, '=', ms);
		if (!tmp)
			return (EXIT_FAILURE);
		value = tmp[1];
	}
	else
		value = NULL;
	return (append_export2(key, value, ms));
}
