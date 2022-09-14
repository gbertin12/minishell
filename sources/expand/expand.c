/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:17:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/14 09:11:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	next_var(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && (between_quote(s, i) || s[i] != '$'))
		i++;
	return (i);
}

static void	expand_cmd(t_token *token, t_minishell *ms)
{
	char	*tmp;
	size_t	i;

	if (token->cmd == NULL)
		return ;
	i = next_var(token->cmd);
	while (token->cmd[i])
	{
		if (token->cmd[i] == 0)
			return ;
		tmp = token->cmd;
		token->cmd = replace_var(token->cmd, i, ms);
		if (!token->cmd)
			token->cmd = tmp;
		else
			ft_free(tmp, ms);
		i = next_var(token->cmd);
	}
}

void	expand(t_minishell *ms)
{
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		expand_cmd(token, ms);
		expand_arg(token, ms);
		delete_quotes(token, ms);
		token = token->next;
	}
}
