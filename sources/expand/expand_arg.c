/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:09:49 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/09 12:59:57 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	expand_arg2(t_arg *arg);

static size_t	count_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		;
	return (i);
}

static char	*read_var(char *s, t_minishell *ms)
{
	size_t	i;
	char	*ret_v;

	i = 0;
	if (s[i] == '?')
		return (ft_strdup("?", ms));
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (ft_strdup("", ms));
	while (s[i] && !is_space(s[i]) && s[i] != '$')
		i++;
	ret_v = ft_substr(s, 0, i, ms);
	return (ret_v);
}

static char	*replace_var_multi(char *s, size_t x, char *value, t_minishell *ms)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	*ret_v;

	tmp2 = ft_substr(s, 0, x, ms);
	ret_v = ft_strjoin(tmp2, value, ms);
	ft_free(tmp2, ms);
	i = x + 1;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	i = size_t_ternary(!ft_isalpha(s[x + 1]) && s[x + 1] != '_', x + 2, i);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	ft_free(tmp, ms);
	return (ret_v);
}

static char	expand_arg_multi(t_arg *arg, char **argv, char *w, t_minishell *ms)
{
	t_arg	*first;
	t_arg	*last;
	char	*tmp;
	t_arg	*a;
	size_t	i;

	i = 0;
	arg->value = replace_var_multi(arg->value, (size_t)(w - arg->value), argv[0], ms);
	tmp = ft_substr(arg->value, (size_t)(w - arg->value), ft_strlen(w), ms);
	arg->value = ft_substr(arg->value, 0, (size_t)(w - arg->value), ms);
	a = ft_malloc(sizeof(t_arg), ms);
	ft_bzero(a, sizeof(t_arg));
	while (argv[++i])
	{
		a->value = ft_strdup(argv[i], ms);
		if (i == 1)
			first = a;
		if (argv[i + 1])
		{
			a->next = ft_malloc(sizeof(t_arg), ms);
			ft_bzero(a->next, sizeof(t_arg));
			a = a->next;
			continue ;
		}
		else
			last = a;
	}
	last->value = ft_strjoin(last->value, tmp, ms);
	last->next = arg->next;
	arg->next = first;
	return (0);
}

char	expand_arg(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	char	*i;
	char	*key;
	char	**arg_value;
	char	*tmp;

	arg = token->arg_head;
	if (!arg)
		return (0);
	i = strchr(arg->value, '$');
	while (arg)
	{
		if (!i)
		{
			arg = arg->next;
			continue ;
		}
		key = read_var(++i, ms);
		if (!key || !*key)
			printf("$%c : not a valid identifier\n", *i);
		tmp = get_env_value(key, ms);
		if (!tmp)
			tmp = ft_strdup("", ms);
		arg_value = ft_split_set(tmp, " \n\r\v\t\f", ms);
		if (count_tab(arg_value) == 1)
		{
			if (arg_value)
				arg->value = replace_var_multi(arg->value, --i - arg->value,
						arg_value[0], ms);
			return (0);
		}
		else if (count_tab(arg_value) > 1)
		{
			if (expand_arg_multi(arg, arg_value, --i, ms))
				return (1);
		}
		else
		{
			arg->value = replace_var_multi(arg->value, --i - arg->value,
					"", ms);
			return (0);
		}
		i = strchr(arg->value, '$');
	}
	return (0);
}
