/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:18:50 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/22 16:46:45 by ccambium         ###   ########.fr       */
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

static void	split_cmd(t_token *token, t_minishell *ms)
{
	int		i;
	char	**split;

	split = ft_split_set(token->cmd, " \n\r\v\t\f", ms);
	if (!split)
		return ;
	if (split[1])
	{
		ft_free(token->cmd, ms);
		token->cmd = split[0];
		i = count_tab(split) - 1;
		while (i > 0)
		{
			token->arg_head = add_front_arg(token->arg_head, split[i], ms);
			if (token->arg_head == NULL)
			{
				free_split(split, ms);
				return ;
			}
			i--;
		}
	}
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
	if (flag)
		split_cmd(token, ms);
	return (EXIT_SUCCESS);
}
