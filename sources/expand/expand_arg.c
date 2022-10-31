/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:09:49 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/31 13:03:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	split_arg2(char **argv, t_minishell *ms,
			t_arg **first, t_arg **last)
{
	size_t	i;
	t_arg	*a;

	i = 0;
	a = ft_malloc(sizeof(t_arg), ms);
	if (!a)
		return (1);
	*first = a;
	while (argv[++i])
	{
		a->value = ft_strdup(argv[i], ms);
		if (argv[i + 1])
		{
			a->next = ft_malloc(sizeof(t_arg), ms);
			if (!a->next)
				return (1);
			a = a->next;
			continue ;
		}
		else
			break ;
	}
	*last = a;
	return (0);
}

char	split_arg(t_arg *arg, t_minishell *ms)
{
	char	**arg_value;
	t_arg	*last;
	t_arg	*first;

	first = NULL;
	last = NULL;
	if (!arg->value)
		return (0);
	arg_value = ft_split_set(arg->value, " \n\r\v\t\f", ms);
	if (!arg_value)
		return (1);
	if (split_arg2(arg_value, ms, &first, &last))
		return (free_split(arg_value, ms), 1);
	arg->value = arg_value[0];
	last->next = arg->next;
	arg->next = first;
	return (free_split(arg_value, ms), 0);
}

static void	expand_arg2(t_token *token, t_minishell *minishell)
{
	t_arg	*arg;

	arg = token->arg_head;
	while (arg)
	{
		if (!arg->value)
		{
			arg = arg->next;
			continue ;
		}
		arg->value = remove_quotes(arg->value, minishell, 0);
		split_arg(arg, minishell);
		arg = arg->next;
	}
}

static char	*next_var(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '$' && !between_quote(s, i))
		i++;
	if (!s[i])
		return (NULL);
	return (s + i);
}

char	expand_arg(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	char	*i;

	arg = token->arg_head;
	while (arg)
	{
		i = next_var(arg->value);
		if (!i || !*i || i[1] == '\0' || is_space(i[1]) || i[1] == '$')
		{
			arg = arg->next;
			continue ;
		}
		arg->value = replace_var(arg->value, i - arg->value, ms);
		if (!arg->value)
			return (1);
	}
	expand_arg2(token, ms);
	return (0);
}
