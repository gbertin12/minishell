/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:32 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/25 09:32:58 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_execute(t_token *token, t_minishell *ms)
{
	token->have_in = have_infile(token);
	token->have_out = have_outfile(token);
	if (token->have_in)
		token->inputfile = open_input(token, ms);
	if (token->have_out)
		token->outputfile = open_output(token);
	printf("%s fd in = %d have in = %d fd out = %d have out = %d NBFILE = %zu\n", token->cmd, token->inputfile, token->have_in, token->outputfile, token->have_out, count_file(token->file_head));
	return (0);
}

int	exec_first_cmd(char **args, t_minishell *ms)
{
	t_token *token;
	char	*path;
	char	**env;
	
	token = ms->t_head;
	if (token->next)
	{
		if (pipe(token->pipefd))
			strerror(errno);
	}
	env = env_to_tab(ms);
	path = make_path(token, ms);
	if (init_execute(token, ms))
		return (1);
	token->pid = fork();
	if (token->pid == -1)
		return (2);
	if (token->pid == 0)
	{
		if (token->have_in)
		{
			if (dup2(token->inputfile, 0) == -1)
				perror("minishell 1 : ");
		}
		if (token->have_out)
		{
			if (token->next)
			{
				close(token->pipefd[0]);
				close(token->pipefd[1]);
			}
			if (dup2(token->outputfile, 1) == -1)
				perror("minishell 2 : ");
		}
		else if (token->next)
		{
			close(token->pipefd[0]);
			if (dup2(token->pipefd[1], 1) == -1)
				perror("minishell 3 : ");
		}
		if (path)
			execve(path, args, env);
		perror("minishell 9 :");
		exit (1);
	}
	return (0);
}

int	redir_out(t_token *token, t_token *last)
{
	(void)last;
	if (token->have_out)
	{
		if (token->next)
		{
			close(token->pipefd[0]);
			close(token->pipefd[1]);
		}
		if (dup2(token->outputfile, 1))
			perror("minishell 6 : ");
	}
	else if (token->next)
	{
		close(token->pipefd[0]);
		if (dup2(token->pipefd[1], 1) == -1)
			perror("minishell 7 : ");
	}
	return (0);
}

int	redir_in(t_token *token, t_token *last)
{
	if (last->have_in)
		close(last->inputfile);
	if (last->have_out)
		close(last->outputfile);
	if (token->have_in)
	{
		if (last->pipefd[0])
			close(last->pipefd[0]);
		if (last->pipefd[1])
			close(last->pipefd[1]);
		if (dup2(token->inputfile, 0))
			perror("minishell 4 : ");
	}
	else
	{
		close(last->pipefd[1]);
		if (dup2(last->pipefd[0], 0))
			perror("minishell 5 : ");
	}
	return (0);
}

int	exec_middle(char **args, t_token *last, t_token *token, t_minishell *ms)
{
	char	*path;
	char	**env;

	ft_putstr_fd("MID\n", 2);
	init_execute(token, ms);
	env = env_to_tab(ms);
	path = make_path(token, ms);
	if (pipe(token->pipefd))
		perror("minishell 8 :");
	token->pid = fork();
	if (token->pid == -1)
		return (2);
	if (token->pid == 0)
	{
		redir_in(token, last);
		redir_out(token, last);
		if (path)
			execve(path, args, env);
		perror("minishell 10 :");
		exit (1);
	}
	return (0);
}

int	exec_last(char **args, t_token *last, t_token *token, t_minishell *ms)
{
	char	*path;
	char	**env;

	init_execute(token, ms);
	env = env_to_tab(ms);
	path = make_path(token, ms);
	
		if (token->have_in)
		{
			if (last->pipefd[0])
				close(last->pipefd[0]);
			if (last->pipefd[1])
				close(last->pipefd[1]);
			if (dup2(token->inputfile, 0))
				perror("minishell 11 : ");
		}
		else
		{
			close(last->pipefd[1]);
			if (dup2(last->pipefd[0], 0) == -1)
				perror("minishell 12 : ");
		}
		if (token->have_out)
		{
			if (dup2(token->outputfile, 1) == -1)
				perror("minishell 13 :");
		}
	token->pid = fork();
	if (token->pid == -1)
		return (2);
	if (token->pid == 0)
	{
		if (path)
			execve(path, args, env);
		perror("minishell 10 :");
		exit (1);
	}
	return (0);
}

int	browse_cmd(t_minishell *ms)
{
	t_token	*token;
	char	**args;
	t_token *last;
	int		tmpin;
	int		tmpout;

	tmpin = (dup(0));
	tmpout = (dup(1));
	g_mode = 1;
	ms->path_absolute = get_path_env(ms);
	token = ms->t_head;
	last = NULL;
	args = args_to_tab(token, ms);
	exec_first_cmd(args, ms);
	last = token;
	if (count_token(ms->t_head) > 1)
		token = token->next;
	while (token->next)
	{
		args = args_to_tab(token, ms);
		exec_middle(args, last, token, ms);
		if (last)
		{
			close(last->pipefd[0]);
			close(last->pipefd[1]);
		}
		last = token;
		token = token->next;
	}
	if (count_token(ms->t_head) > 1)
	{
		args = args_to_tab(token, ms);
		exec_last(args, last, token, ms);
	}
	if (last)
	{
		close(last->pipefd[0]);
		close(last->pipefd[1]);
	}
	token = ms->t_head;
	while (token)
	{
		waitpid(token->pid, NULL, 0);
		token = token->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	return (1);
}