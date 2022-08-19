/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_arg_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:59:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/19 12:59:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	next_arg(char *s, t_token *token, t_minishell *ms)
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

long long	next_arg_w_quote(char *s, t_token *token, t_minishell *ms)
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
