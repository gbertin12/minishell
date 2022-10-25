/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:47:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 18:17:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_default_path(char *path, t_minishell *ms)
{
	char	*err;

	err = NULL;
	err = ft_strjoin(err, "minishell: cd: ", ms);
	if (!err)
		return (NULL);
	err = ft_strjoin(err, path, ms);
	if (!err)
		return (NULL);
	err = ft_strjoin(err, ": ", ms);
	if (!err)
		return (NULL);
	return (err);
}

int	check_err(char *path, t_minishell *ms)
{
	char	*err;

	err = make_default_path(path, ms);
	if (!err)
		return (1);
	if (errno == 116)
	{
		err = ft_strjoin(err, "State file handle\n", ms);
		if (!err)
			return (1);
	}
	else
	{
		err = ft_strjoin(err, strerror(errno), ms);
		if (!err)
			return (1);
		err = ft_strjoin(err, "\n", ms);
		if (!err)
			return (1);
	}
	ft_putstr_fd(err, 2);
	return (1);
}

static void	exec_child(t_token *token, t_minishell *ms)
{
	init_execute(token, ms);
	redir_out(token);
	if (_cd(token, ms))
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

int	exec_cd(t_token *token, t_minishell *ms)
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
		if (_cd(token, ms))
			return (1);
		else
			return (0);
	}
	return (0);
}
