/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 10:24:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	search_next_sep(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	while(s[i] == "=" || s[i] == "|" || s[i] == ">"
		|| s[i] == "<" || s[i] == " " || s[i] != NULL)
		i++;
	return (i);
}

void	parsing(char *s, t_minishell *ms)
{
	t_token *token;
	t_token *n_token;
	size_t	i;

	ft_malloc(sizeof(token), ms);
	ft_memset(token, 0, sizeof(t_token));
	ms->t_head = token;
	if (s[0] == '\0')
		return ;
	i = -1;
	while(s[++i])
	{
		
		if (ms->t_head == NULL)
			ms->t_head = token;
	}
	return ;
}