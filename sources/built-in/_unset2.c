/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:39:10 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 12:40:05 by gbertin          ###   ########.fr       */
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
