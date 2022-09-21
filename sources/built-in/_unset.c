/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:50:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/20 17:22:29 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_elem(t_env *before, t_env *after, t_env *head)
{
	if (!before && !after)
		head->next = NULL;
	if (!before)
		head->next = after;
	else if (after == NULL)
		before->next = NULL;
	else
		before->next = after;
}

static int	_unset2(char *key, t_env *e_before, t_env *e_env, t_minishell *ms)
{
	if (!ft_strncmp(key, e_env->key, ft_strlen(key)))
	{
		unset_elem(e_before, e_env->next, ms->e_head);
		ft_free(e_env->key, ms);
		ft_free(e_env->value, ms);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	_unset(t_arg *arg, t_minishell *ms)
{
	t_env	*e_env;
	t_env	*e_before;
	int		flag;

	flag = 0;
	while (arg)
	{
		e_before = NULL;
		e_env = ms->e_head;
		if (check_key_env(arg->value))
		{
			print_not_valid_identifier("unset", arg->value);
			flag = 1;
		}
		while (e_env)
		{
			_unset2(arg->value, e_before, e_env, ms);
			e_before = e_env;
			e_env = e_env->next;
		}
		arg = arg->next;
	}
	if (flag == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	exec_unset(t_token *token, t_minishell *ms)
{
	init_execute(token);
	if (token->next)
	{
		if (pipe(token->pipefd))
			perror("minishell ");
	}
	if (token->arg_head)
	{
		if (_unset(token->arg_head, ms))
		{
			ms->l_retv = 1;
			return (1);
		}
	}
	ms->l_retv = 0;
	return (0);
}
