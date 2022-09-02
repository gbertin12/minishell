/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_of_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:49:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 12:54:15 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	*first(t_exec *exec, t_minishell *ms)
{
	exec->args = args_to_tab(exec->token, ms);
	if (check_is_built_in(exec->token))
		exec->l_retv = exec_builtin(exec->token, ms);
	else
	{
		if (exec->token->next)
		{
			if (pipe(exec->token->pipefd))
				perror(" minishell ");
		}
		exec_first_cmd(exec, ms);
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
	exec->args = args_to_tab(exec->token, ms);
	if (check_is_built_in(exec->token))
		;
	else
		exec_middle(exec->args, exec, ms);
	close(exec->last->pipefd[0]);
	close(exec->last->pipefd[1]);
	exec->last = exec->token;
	exec->token = exec->token->next;
	return (exec);
}

t_exec	*last(t_exec *exec, t_minishell *ms)
{
	exec->args = args_to_tab(exec->token, ms);
	if (check_is_built_in(exec->token))
		;
	else
		exec_last(exec->args, exec, ms);
	return (exec);
}
