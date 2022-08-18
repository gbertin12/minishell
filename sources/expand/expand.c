/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:17:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 12:32:49 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	expend_arg(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	size_t	i;
	char	*tmp;

	arg = token->arg_head;
	while (arg)
	{
		if (arg->value)
		{
			i = 0;
			while (arg->value[i])
			{
				i = next_var(&arg->value[i]);
				if (arg->value[i] == 0)
					break ;
				tmp = arg->value;
				arg->value = replace_var(&arg->value[i], ms);
				if (!arg->value)
					arg->value = tmp;
				else
					ft_free(tmp, ms);
			}
		}
		arg = arg->next;
	}
}

long long	expend_file(t_token *token, t_minishell *ms)
{
	t_file	*file;
	size_t	i;
	char	*tmp;

	file = token->file_head;
	while (file)
	{
		if (file->path)
		{
			i = 0;
			while (file->path[i])
			{
				i = next_var(&file->path[i]);
				if (file->path[i] == 0)
					break ;
				tmp = file->path;
				file->path = replace_var(&file->path[i], ms);
				if (!file->path)
					file->path = tmp;
				else
					ft_free(tmp, ms);
			}
		}
		file = file->next;
	}
}

long long	expend_cmd(t_token *token, t_minishell *ms)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (token->cmd[i])
	{
		i = next_var(&token->cmd[i]);
		if (token->cmd[i] == 0)
			break ;
		tmp = token->cmd;
		token->cmd = replace_var(token->cmd[i], ms);
		if (!token->cmd)
			token->cmd = tmp;
		else
			ft_free(tmp, ms);
	}
}

char	expand(t_minishell *ms)
{
	char	*s;
	t_token	*token;
	char	flag[2];

	token = ms->t_head;
	while (token)
	{
		expand_cmd(token, ms);
		expend_arg(token, ms);
		expand_file(token, ms);
		token = token->next;
	}
}
