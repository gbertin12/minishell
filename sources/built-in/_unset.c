/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:50:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/31 11:04:29 by gbertin          ###   ########.fr       */
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

int	_unset(char *key, t_minishell *ms)
{
	t_env	*e_env;
	t_env	*e_before;

	e_before = NULL;
	e_env = ms->e_head;
	if (check_key_env(key))
	{
		ft_putstr_fd("minishell: unset: \"", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("` not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	if (!e_env || !do_env_key_exist(key, ms))
		return (EXIT_SUCCESS);
	while (e_env)
	{
		if (!_unset2(key, e_before, e_env, ms))
			return (EXIT_SUCCESS);
		e_before = e_env;
		e_env = e_env->next;
	}
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
		if (_unset(token->arg_head->value, ms))
		{
			ms->l_retv = 1;
			return (1);
		}
	}
	ms->l_retv = 0;
	return (0);
}
