/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:32 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/31 12:08:22 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_execute(t_token *token)
{
// 	token->inputfile = 0;
// 	token->outputfile = 0;
// 	token->have_in = have_infile(token);
// 	token->have_out = have_outfile(token);
	if (token->have_in)
	{
		//token->inputfile = open_input(token);
		
		if (token->inputfile < 0)
			return (1);
	}
	if (token->have_out)
	{
		//token->outputfile = open_output(token);
		if (token->outputfile < 0)
			return (1);
	}
	return (0);
}

t_exec	*start_browse_cmd(t_minishell *ms)
{
	t_exec	*exec;

	exec = ft_malloc(sizeof(t_exec), ms);
	if (!ms->t_head)
		return (NULL);
	exec->err = 0;
	exec->last = NULL;
	exec->env = env_to_tab(ms);
	exec->token = ms->t_head;
	exec->tmpin = (dup(0));
	exec->tmpout = (dup(1));
	g_mode = 1;
	open_all(ms);
	exec->path_absolute = get_path_env(ms);
	return (exec);
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
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	g_mode = 0;
	printf("RETURN STATUS : %d\n", WEXITSTATUS(status));
	ms->l_retv = WEXITSTATUS(status);
	return (0);
}

int	browse_cmd(t_minishell *ms)
{
	t_exec	*exec;
	t_token	*token;

	exec = start_browse_cmd(ms);
	if (!exec)
		return (1);
	exec = first(exec, ms);
	if (exec->err)
		return (end_browse_cmd(exec, ms));
	token = exec->token;
	while (token->next)
	{
		exec = middle(exec, ms);
		token = exec->token;
	}
	if (count_token(ms->t_head) > 1)
		exec = last(exec, ms);
	return (end_browse_cmd(exec, ms));
}
