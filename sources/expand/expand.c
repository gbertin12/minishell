/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:17:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 15:17:35 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		{
			token->cmd = NULL;
			break ;
		}
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
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
