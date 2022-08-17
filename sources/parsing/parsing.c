/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 17:44:28 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	token = ft_malloc(sizeof(t_token), ms);
	ft_memset(token, 0, sizeof(t_token));
	if (!s)
		return ;
	i = 0;
	i = next_arg(&s[i], token, ms);
	while (s[i + 1] != '\0')
	{
		while ((s[i] != '|' && s[i] != '>' && s[i] != '<'
			&& !is_space(s[i]) && s[i] != '\0'))
			i++;
		while (is_space(s[i]))
			i++;
		if (s[i] == '|' && s[i] != '\0')
		{
			if (ms->t_head == NULL)
				ms->t_head = token;
			else
				add_end_token(ms->t_head, token);
			token = ft_malloc(sizeof(t_token), ms);
			ft_memset(token, 0, sizeof(t_token));
			i++;
		}
		if (is_space(s[i]) || s[i] == '|')
			i++;
		x = next_arg(&s[i], token, ms);
		if (x < 0)
			return ;
		i += (size_t)x;
	}
	if (ms->t_head == NULL)
		ms->t_head = token;
	else
		add_end_token(ms->t_head, token);
}
