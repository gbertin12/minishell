/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/19 12:36:24 by gbertin          ###   ########.fr       */
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

static char			*get_cmd_w_quote(char *cmd, char c, t_minishell *ms)
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
	while(y < i && i != 1)
	{
		s_ret[y - 1] = cmd[y];
		y++;
	}
	s_ret[y- 1] = '\0';
	return (s_ret);
}
static void	add_arg_w_quote(char *cmd, char quote, t_token *token, t_minishell *ms)
{
	t_arg	*n_arg;

	if (!cmd || cmd[0] == '\0')
		return ;
	n_arg = ft_malloc(sizeof(t_arg), ms);
	n_arg->value = cmd;
	n_arg->next = NULL;
	if (quote == '\'')
		n_arg->apos = 1;
	if (token->arg_head == NULL)
		token->arg_head = n_arg;
	else
		add_end_arg(token->arg_head, n_arg);
}

static long long	next_arg_w_quote(char *s, t_token *token, t_minishell *ms)
{
	char		*cmd;
	char		quote;

	quote = s[0];
	if (!ft_strchr(s, quote))
		cmd = get_cmd_w_quote(s, quote, ms);
	else
	{
		if (quote == '\'')
			ft_putstr_fd("Error parsing : \' not close\n", 0);
		else
			ft_putstr_fd("Error parsing : \" not close\n", 0);
		return (-2);
	}		
	if (token->cmd == NULL)
	{
		if (quote == '\'')
			token->apos = 1;
		token->cmd = cmd;
	}
	else
		add_arg_w_quote(cmd, quote, token, ms);
	return (ft_strlen(cmd) + 2);
}

static size_t	next_arg(char *s, t_token *token, t_minishell *ms)
{
	size_t	size;

	if (s[0] == '>')
		return (add_output(s, token, ms));
	else if (s[0] == '<')
		return (add_input(s, token, ms));
	if (s[0] == '\'' || s[0] == '\"')
		return (next_arg_w_quote(s, token, ms));
	if (token->cmd == NULL)
	{
		size = search_next_sep(s);
		token->cmd = ft_substr(s, 0, size, ms);
	}
	else
		add_arg(s, token, ms);
	return (0);
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
	{
		//printf("here\n");
		return ;
	}
	parsing2(s, i, token, ms);
}
