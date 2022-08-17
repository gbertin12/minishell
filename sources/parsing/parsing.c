/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 12:20:44 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	search_next_sep(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while(s[i] != '=' && s[i] != '|' && s[i] != '>' && s[i] != '<' 
		&& s[i] != ' ' && s[i] != '\0')
		i++;
	return (i);
}

// static char is_space(char c)
// {
// 	return (c == '\f' || c == '\n' || c == '\r'
// 		|| c == '\t' || c == '\v' || c == ' ');
// }

static size_t next_arg(char *s, t_token *token, t_minishell *ms)
{
	size_t	size;
	t_arg	*n_arg;
	size = search_next_sep(s);
	if (token->cmd == NULL)
		token->cmd = ft_substr(s, 0, size, ms);
	else
	{
		n_arg = ft_malloc(sizeof(t_arg), ms);
		n_arg->value = ft_substr(s, 0, size, ms);
		n_arg->next = NULL;
		if (token->arg_head == NULL)
			token->arg_head = n_arg;
		else
			add_end_arg(token->arg_head, n_arg);
	}
	//fill_io();
	return (size - 1);
}

void	parsing(char *s, t_minishell *ms)
{
	t_token *token;
	size_t	i;

	token = ft_malloc(sizeof(t_token), ms);
	ft_memset(token, 0, sizeof(t_token));
	token->next = NULL;
	token->arg_head = NULL;
	token->cmd = NULL;
	ms->t_head = token;
	if (!s)
		return ;
	i = 0;
	i = next_arg(&s[i], token, ms);
	while(s[i] != '\0')
	{
		printf("i = %lu\n", i);
		i += search_next_sep(s);
		if (s[i] == '|')
		{
			if (ms->t_head == NULL)
				ms->t_head = token;
			else
				add_end_token(ms->t_head, token);
			token = ft_malloc(sizeof(t_token), ms);
			token->next = NULL;
			token->arg_head = NULL;
			token->cmd = NULL;
		}
		i += next_arg(&s[i], token, ms);
	}
}