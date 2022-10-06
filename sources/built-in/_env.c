/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:55:17 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/05 11:53:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_child(t_token *token, t_minishell *ms)
{
	if (init_execute(token))
		exit_child(1, ms);
	redir_out(token);
	if (_env(ms))
		exit_child(1, ms);
	exit_child(0, ms);
	return (0);
}

int	_env(t_minishell *ms)
{
	t_env	*env;

	env = ms->e_head;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	exec_env(t_token *token, t_minishell *ms)
{
	modify_env("_", get_last_arg(token), ms);
	if (token->arg_head)
		return (1);
	if (token->next)
	{
		if (pipe(token->pipefd))
		{
			perror("");
			return (1);
		}
	}
	token->pid = fork();
	if (token->pid == 0)
		exec_child(token, ms);
	return (0);
}
