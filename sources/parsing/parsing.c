/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/30 12:14:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*new_token(t_token *token, t_minishell *ms)
{
	if (token)
		add_end_token(token, ms);
	token = (t_token *)ft_malloc(sizeof(t_token), ms);
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	token->cmd = NULL;
	return (token);
}

static size_t	skip_spaces(char *s)
{
	size_t	ret_v;

	ret_v = 0;
	while (is_space(s[ret_v]))
		ret_v++;
	return (ret_v);
}

static char	is_token_empty(t_token *token)
{
	if (!token)
		return (0);
	return ((!token->cmd || !token->cmd[0])
		&& !token->arg_head && !token->file_head);
}

char	parsing2(char *s, size_t i, t_token *token, t_minishell *ms)
{
	long long	x;

	while (s[i] != '\0')
	{
		i += search_next_sep(&s[i]);
		i += skip_spaces(&s[i]);
		if (s[i] == '|')
		{
			token = new_token(token, ms);
			if (!token)
				return (0);
			i++;
		}
		x = next_arg(&s[i], token, ms);
		if (x < 0)
			return (x);
		i += (size_t)x;
	}
	if (is_token_empty(token) && s[0])
	{
		printf("minishell : syntax error near unexpected token `newline\"\n");
		return (1);
	}
	add_end_token(token, ms);
	return (0);
}

char	parsing(char *s, t_minishell *ms)
{
	t_token			*token;
	long long		i;

	token = new_token(NULL, ms);
	if (!token || !s)
		return (0);
	i = next_arg(s, token, ms);
	if (i < 0)
		return (i);
	return (parsing2(s, i, token, ms));
}
