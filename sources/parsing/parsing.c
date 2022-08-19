/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/19 13:04:27 by gbertin          ###   ########.fr       */
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

static char	*get_cmd_w_quote(char *cmd, char c, t_minishell *ms)
{
	size_t	i;
	char	*s_ret;
	size_t	y;

	i = 1;
	y = 1;
	while (cmd[i] != c)
		i++;
	s_ret = ft_malloc(i, ms);
	if (!s_ret)
		return (NULL);
	while (y < i && i != 1)
	{
		s_ret[y - 1] = cmd[y];
		y++;
	}
	s_ret[y - 1] = '\0';
	return (s_ret);
}

static size_t	skip_spaces(char *s)
{
	size_t	ret_v;

	ret_v = 0;
	while (is_space(s[ret_v]))
		ret_v++;
	return (ret_v);
}

void	parsing2(char *s, size_t i, t_token *token, t_minishell *ms)
{
	long long	x;

	while (s[i + 1] != '\0')
	{
		i += search_next_sep(&s[i]);
		i += skip_spaces(&s[i]);
		if (s[i] == '|')
		{
			token = new_token(token, ms);
			if (!token)
				return ;
			i++;
		}
		i += skip_spaces(&s[i]);
		x = next_arg(&s[i], token, ms);
		if (x < 0)
			return ;
		i += (size_t)x;
	}
	add_end_token(token, ms);
}

void	parsing(char *s, t_minishell *ms)
{
	t_token			*token;
	size_t			i;

	token = new_token(NULL, ms);
	if (!token || !s)
		return ;
	i = next_arg(s, token, ms);
	if (i < 0)
		return ;
	parsing2(s, i, token, ms);
}
