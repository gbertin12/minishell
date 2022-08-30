/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:52:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/30 12:24:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{	
		ft_putstr_fd("IN CHILD\n", 2);
		init_execute(token);
		redir_out(token);
		if (_env(ms))
			exit(1);
		exit(0);
	}
	return (1);
}
