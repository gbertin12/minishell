/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:18:50 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/10 11:09:14 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	expand_cmd(t_token *token, t_minishell *ms)
{
	size_t	i;
	char	flag;

	flag = 0;
	if (token->cmd == NULL)
		return (0);
	i = next_var(token->cmd);
	while (token->cmd[i])
	{
		flag = 1;
		token->cmd = replace_var(token->cmd, i, ms);
		if (!token->cmd)
			return (1);
		i = next_var(token->cmd);
	}
	return (EXIT_SUCCESS);
}
