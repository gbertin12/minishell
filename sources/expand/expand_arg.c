/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:09:49 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/03 16:04:35 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	split_arg(t_arg *arg, t_minishell *ms)
{
	int		i;
	char	**split;

	split = ft_split_set(arg->value, " \n\r\v\t\f", ms);
	if (!split || !split[0])
		return ;
	ft_free(arg->value, ms);
	arg->value = split[0];
	if (!split[1])
		return ;
	i = count_tab(split) - 1;
	while (i > 0)
	{
		arg->next = add_front_arg(arg->next, split[i], ms);
		if (arg->next == NULL)
		{
			free_split(split, ms);
			return ;
		}
		i--;
	}
}

static size_t	next_var(char *s)
{
	size_t	i;

	i = 0;
	while ((s && s[i]) || between_quote(s, i))
	{
		if (s[i] == '$' && !between_quote(s, i) && s[i + 1] != '\0'
			&& !is_space(s[i + 1]) && s[i + 1] != '$')
			return (i);
		i++;
	}
	return (i);
}

static char	in_quote(char *s, size_t x)
{
	char	d_quote;
	char	quote;
	size_t	i;

	quote = 0;
	d_quote = 0;
	i = 0;
	while (s && s[i] && i <= x)
	{
		if (s[i] == '"' && !quote)
			d_quote = char_ternary(d_quote, 0, 1);
		if (s[i] == '\'' && !d_quote)
			quote = char_ternary(quote, 0, 1);
		i++;
	}
	return (quote + d_quote);
}

char	expand_arg(t_token *token, t_minishell *ms)
{
	size_t	i;
	t_arg	*arg;

	arg = token->arg_head;
	if (arg == NULL)
		return (0);
	while (arg)
	{
		i = next_var(arg->value);
		if (!arg->value || !arg->value[i])
		{
			arg = arg->next;
			continue ;
		}
		arg->value = replace_var(arg->value, i, ms);
		if (!arg->value)
			return (1);
		if (!in_quote(arg->value, i))
			split_arg(arg, ms);
	}
	return (EXIT_SUCCESS);
}
