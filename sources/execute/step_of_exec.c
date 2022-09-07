/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_of_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:49:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/07 17:20:02 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int		check_have_char(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (ft_isprint(cmd[i]) && !is_space(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_last_arg(t_token *token)
{
	t_arg	*arg;

	if (!token->arg_head)
		return (token->cmd);
	arg = token->arg_head;
	while (arg->next)
		arg = arg->next;
	return (arg->value);
}

t_exec	*first(t_exec *exec, t_minishell *ms)
{
	if (check_have_char(exec->token->cmd))
	{
		exec->args = args_to_tab(exec->token, ms);
		if (check_is_built_in(exec->token))
			exec->l_retv = exec_builtin(exec->token, ms);
		else
		{
			if (exec->token->next)
			{
				if (pipe(exec->token->pipefd) == -1)
					return (exec);
			}
			exec_first_cmd(exec, ms);
		}
		modify_env("_", get_last_arg(exec->token), ms);
	}
	exec->last = exec->token;
	if (count_token(ms->t_head) > 1)
		exec->token = exec->token->next;
	else
		exec->err = 1;
	return (exec);
}

t_exec	*middle(t_exec *exec, t_minishell *ms)
{
	if (check_have_char(exec->token->cmd))
	{
		exec->args = args_to_tab(exec->token, ms);
		if (check_is_built_in(exec->token))
			exec->l_retv = exec_builtin(exec->token, ms);
		else
			exec_middle(exec->args, exec, ms);
		modify_env("_", get_last_arg(exec->token), ms);
		close(exec->last->pipefd[0]);
		close(exec->last->pipefd[1]);
	}
	exec->last = exec->token;
	exec->token = exec->token->next;
	return (exec);
}

t_exec	*last(t_exec *exec, t_minishell *ms)
{
	if (check_have_char(exec->token->cmd))
	{
		exec->args = args_to_tab(exec->token, ms);
		if (check_is_built_in(exec->token))
			exec->l_retv = exec_builtin(exec->token, ms);
		else
			exec_last(exec->args, exec, ms);
		modify_env("_", get_last_arg(exec->token), ms);
	}
	return (exec);
}
