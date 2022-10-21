/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:50:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 10:02:32 by gbertin          ###   ########.fr       */
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
	if (!key || !key[0])
		return (EXIT_SUCCESS);
	if (!ft_strncmp(key, e_env->key, ft_strlen(key) + 1))
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

static void	exec_child(t_token *token, t_minishell *ms)
{
	init_execute(token, ms);
	redir_out(token);
	if (_unset(token->arg_head, ms))
		exit_child(1, ms);
	else
		exit_child(0, ms);
}

static int	exec_in_child(t_token *token, t_minishell *ms)
{
	int	ret_v;

	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		if (ms->exec->last)
		{
			close(ms->exec->last->pipefd[0]);
			close(ms->exec->last->pipefd[1]);
		}
		exec_child(token, ms);
		ret_v = g_lretv;
		exit_child(ret_v, ms);
	}
	return (1);
}

int	exec_unset(t_token *token, t_minishell *ms)
{
	if (count_token(ms->t_head) > 1)
		exec_in_child(token, ms);
	else
	{
		if (init_exec_no_child(token) == 130)
			return (130);
		if (init_exec_no_child(token) == -1)
			return (0);
		if (init_exec_no_child(token) == 1)
			return (1);
		if (_unset(token->arg_head, ms))
			return (1);
		else
			return (0);
	}
	return (0);
}
