/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 03:57:50 by ccambium         ###   ########.fr       */
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
	return (token);
}

static size_t	next_arg(char *s, t_token *token, t_minishell *ms)
{
	size_t	size;

	if (s[0] == '>')
		return (add_output(s, token, ms));
	else if (s[0] == '<')
		return (add_input(s, token, ms));
	else if (token->cmd == NULL)
	{
		size = search_next_sep(s);
		token->cmd = ft_substr(s, 0, size, ms);
	}
	else
		add_arg(s, token, ms);
	return (0);
}

void	parsing(char *s, t_minishell *ms)
{
	t_token			*token;
	size_t			i;
	long long int	x;

	token = new_token(NULL, ms);
	if (!token || !s)
		return ;
	i = next_arg(s, token, ms);
	while (s[i + 1] != '\0')
	{
		i += search_next_sep(&s[i]);
		while (is_space(s[i]))
				i++;
		if (s[i] == '|')
		{
			token = new_token(token, ms);
			if (!token)
				return ;
			i++;
		}
		while (is_space(s[i]))
			i++;
		x = next_arg(&s[i], token, ms);
		if (x < 0)
			return ;
		i += (size_t)x;
	}
	add_end_token(token, ms);
}
