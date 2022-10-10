/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:17:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/10 16:27:31 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	split_cmd(t_token *token, t_minishell *ms)
{
	int		i;
	char	**split;

	split = ft_split_set(token->cmd, " \n\r\v\t\f", ms);
	if (!split || !split[0])
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

static void	remove_first_arg(t_token *token, t_minishell *ms)
{
	t_arg	*arg;

	arg = token->arg_head;
	arg = arg->next;
	ft_free(token->arg_head->value, ms);
	ft_free(token->arg_head, ms);
	token->arg_head = arg;
}

static void	replace_cmd(t_token *token, t_minishell *ms)
{
	while (!token->cmd || token->cmd[0] == '\0')
	{
		if (token->arg_head)
		{
			token->cmd = token->arg_head->value;
			remove_first_arg(token, ms);
		}
		else
			break ;
	}
}

char	expand(t_minishell *ms)
{
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		if (expand_cmd(token, ms))
			return (1);
		if (expand_arg(token, ms))
			return (1);
		delete_quotes(token, ms);
		replace_cmd(token, ms);
		remove_null(token, ms);
		split_cmd(token, ms);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
