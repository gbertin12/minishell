/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:57:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 11:01:06 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*biggest(t_minishell *ms)
{
	t_env	*ret_v;
	t_env	*env;

	env = ms->e_head;
	ret_v = ms->e_head;
	while (env)
	{
		if (ft_strncmp(env->key, ret_v->key, ft_strlen(env->key)) > 0)
			ret_v = env;
		env = env->next;
	}
	return (ret_v);
}

static t_env	*next_declare(t_minishell *ms, t_env *last)
{
	t_env	*env;
	t_env	*ret_v;

	env = ms->e_head;
	ret_v = biggest(ms);
	if (ret_v == last)
		return (NULL);
	while (env)
	{
		if (!last)
		{
			if (ft_strncmp(env->key, ret_v->key, ft_strlen(env->key) + 1) < 0)
				ret_v = env;
		}
		else
		{
			if (ft_strncmp(env->key, last->key, ft_strlen(env->key) + 1) > 0
				&& ft_strncmp(env->key, ret_v->key,
					ft_strlen(env->key) + 1) < 0)
				ret_v = env;
		}
		env = env->next;
	}
	return (ret_v);
}

static int	declaration(t_minishell *ms)
{
	t_env	*env;

	env = next_declare(ms, NULL);
	while (env)
	{
		if (env->value)
			printf("export %s=\"%s\"\n", env->key, env->value);
		else
			printf("export %s\n", env->key);
		env = next_declare(ms, env);
	}
	return (EXIT_SUCCESS);
}

static int	_export2(t_arg *arg, t_minishell *ms)
{
	char	*key;
	char	*value;
	char	**tmp;

	tmp = ft_split(arg->value, '=', ms);
	if (!tmp)
		return (EXIT_FAILURE);
	key = ft_strtrim(tmp[0], " \t\n\r\f\v", ms);
	if (!key)
		return (EXIT_FAILURE);
	if (check_key_env(key) || arg->value[0] == '=')
		return (print_not_valid_identifier("export", arg->value));
	ft_free(tmp[0], ms);
	value = ft_superjoin(arg->value, tmp, ms);
	if (do_env_key_exist(key, ms))
		replace_env_value(key, value, ms);
	else
		add_env_key_value(key, value, ms);
	ft_free(tmp, ms);
	return (EXIT_SUCCESS);
}

int	_export(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	int		error;

	if (token == NULL)
		return (EXIT_FAILURE);
	if (no_valid_arg(token->arg_head))
		return (declaration(ms));
	arg = token->arg_head;
	error = 0;
	while (arg != NULL)
	{
		if (arg->value && arg->value[0])
		{
			if (check_append_export(arg->value) && append_export(arg, ms))
					error = 0;
			else if (_export2(arg, ms))
				error = 1;
		}
		arg = arg->next;
	}
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
