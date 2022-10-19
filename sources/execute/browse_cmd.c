/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:32 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/19 15:08:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	have_child(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->pid != 0)
		return (1);
	return (0);
}

int	return_value_child(int status, t_exec *exec, t_minishell *ms)
{
	if (have_child(ms->t_head))
	{
		if (WIFSIGNALED(status))
		{
			if (status == 131)
				exec->l_retv = status;
			else
				exec->l_retv = status + 128;
		}
		else
			exec->l_retv = WEXITSTATUS(status);
	}
	return (exec->l_retv);
}

t_exec	*start_browse_cmd(t_minishell *ms)
{
	exec_signals();
	ms->exec = ft_malloc(sizeof(t_exec), ms);
	if (!ms->t_head || !ms->exec)
		return (NULL);
	ft_memset(ms->exec, 0, sizeof(t_exec));
	ms->exec->env = env_to_tab(ms);
	ms->exec->token = ms->t_head;
	ms->exec->tmpin = dup(0);
	if (ms->exec->tmpin == -1)
		return (NULL);
	ms->exec->tmpout = dup(1);
	if (ms->exec->tmpout == -1)
		return (NULL);
	open_all(ms);
	ms->exec->path_absolute = get_path_env(ms);
	return (ms->exec);
}

int	end_browse_cmd(t_exec *exec, t_minishell *ms)
{
	int		status;

	if (exec->last)
	{
		close(exec->last->pipefd[0]);
		close(exec->last->pipefd[1]);
	}
	exec->token = ms->t_head;
	while (exec->token)
	{
		waitpid(exec->token->pid, &status, 0);
		exec->token = exec->token->next;
	}
	if (dup2(exec->tmpin, 0) == -1)
		return (1);
	if (dup2(exec->tmpout, 1) == -1)
		return (1);
	exec->l_retv = return_value_child(status, exec, ms);
	close(exec->tmpin);
	close(exec->tmpout);
	g_lretv = exec->l_retv;
	return (0);
}

int	browse_cmd(t_minishell *ms)
{
	t_exec	*exec;
	t_token	*token;

	exec = start_browse_cmd(ms);
	if (!exec)
		return (1);
	if (exec->token)
		exec = first(exec, ms);
	if (exec->err)
		return (end_browse_cmd(exec, ms));
	token = exec->token;
	while (token->next)
	{
		if (exec->token->cmd)
			exec = middle(exec, ms);
		token = exec->token;
	}
	if (count_token(ms->t_head) > 1 && exec->token->cmd)
		exec = last(exec, ms);
	return (end_browse_cmd(exec, ms));
}
