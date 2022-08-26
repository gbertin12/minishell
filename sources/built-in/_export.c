/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:57:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/26 17:42:39 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*next_declare(t_minishell *ms, t_env *last)
{
	t_env	*env;
	char	flag;
	t_env	*ret_v;

	env = ms->e_head->next;
	ret_v = ms->e_head;
	flag = 0;
	while (env)
	{
		if (last)
		{
			if (strcmp(env->key, last->key) > 0
				&& strcmp(env->key, ret_v->key) < 0)
			{
				flag = 1;
				ret_v = env;
			}
		}
		else
		{
			if (strcmp(env->key, ret_v->key) < 0)
			{
				flag = 1;
				ret_v = env;
			}
		}
		env = env->next;
	}
	if (!flag)
		return (NULL);
	return (ret_v);
}

static int	declaration(t_minishell *ms)
{
	t_env	*env;

	env = next_declare(ms, NULL);
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s=\n", env->key);
		env = next_declare(ms, env);
	}
	return (EXIT_SUCCESS);
}

static void	add_key_with_empty_value(char *s, t_minishell *ms)
{
	if (do_env_key_exist(s, ms))
		replace_env_value(s, NULL, ms);
	else
		add_env_key_value(s, NULL, ms);
}

static int	_export2(t_arg *arg, t_minishell *ms)
{
	char	*key;
	char	*value;
	char	**tmp;

	if (check_key_env(&arg->value[0]))
	{
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putstr_fd(&arg->value[0], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	else if (ft_strchr(arg->value, '=') == NULL)
	{
		add_key_with_empty_value(arg->value, ms);
		return (EXIT_SUCCESS);
	}
	tmp = ft_split(arg->value, '=', ms);
	key = ft_strtrim(tmp[0], " \t\n\r\f\v", ms);
	ft_free(tmp[0], ms);
	value = ft_superjoin(tmp, ms);
	if (do_env_key_exist(key, ms))
		replace_env_value(key, value, ms);
	else
		add_env_key_value(key, value, ms);
	arg = arg->next;
	ft_free(tmp, ms);
	return (EXIT_SUCCESS);
}

int	_export(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	int		error;

	if (token == NULL)
		return (EXIT_FAILURE);
	if (!token->arg_head)
		return (declaration(ms));
	arg = token->arg_head;
	error = 0;
	while (arg != NULL)
	{
		if (_export2(arg, ms))
			error = 1;
		arg = arg->next;
	}
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
