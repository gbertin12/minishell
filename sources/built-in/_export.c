/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:57:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 10:06:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_env_value(char *key, char *value, t_minishell *ms)
{
	t_env	*env;

	env = ms->e_head;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			ft_free(env->value, ms);
			env->value = value;
			ft_free(env->key, ms);
			env->key = key;
			return ;
		}
		env = env->next;
	}
}

static void	add_env_key_value(char *key, char *value, t_minishell *ms)
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

int	_export(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	char	*key;
	char	*value;
	char	**tmp;

	if (token == NULL)
		return (EXIT_SUCCESS);
	arg = token->arg_head;
	while (arg != NULL)
	{
		if (ft_strchr(arg->value, '=') == NULL)
		{
			arg = arg->next;
			continue ;
		}
		tmp = ft_split(arg->value, '=', ms);
		key = tmp[0];
		value = ft_superjoin(tmp, ms);
		if (do_env_key_exist(key, ms))
			replace_env_value(key, value, ms);
		else
			add_env_key_value(key, value, ms);
		arg = arg->next;
		ft_free(tmp, ms);
	}
	return (EXIT_SUCCESS);
}
