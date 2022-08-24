/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:32 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/23 22:59:11 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path_env(t_minishell *ms)
{
	char	**all_path;
	char	**env;
	size_t	i;

	i = 0;
	env = env_to_tab(ms);
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			while (*env[i] != '/' && *env[i] != '\0')
				env[i]++;
			all_path = ft_split(env[i], ':', ms);
			if (!all_path)
				return (NULL);
			return (all_path);
		}
		i++;
	}
	return (NULL);
}

int	ft_search_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*make_path(t_token *token, t_minishell *ms)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	if (ms->path_absolute == NULL || ft_search_char(token->cmd))
	{
		if (access(token->cmd, 0) == 0)
			return (ft_strdup(token->cmd, ms));
		return (NULL);
	}
	while (ms->path_absolute[i] != NULL)
	{
		tmp = ft_strjoin(ms->path_absolute[i], "/", ms);
		path = ft_strjoin(tmp, token->cmd, ms);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int		init_execute(t_token *token, t_minishell *ms)
{
	int oldfd;
	
	token->have_in = have_infile(token);
	token->have_out = have_outfile(token);
	if (token->have_in)
	{
		token->inputfile = open_input(token, ms);
	}
	if (token->have_out)
	{
		oldfd = open_input(token, ms);
		token->inputfile = dup(oldfd);
		close(oldfd);
	}
		token->outputfile = dup(open_output(token));
	printf("%s fd in = %d have in = %d fd out = %d have out = %d NBFILE = %zu\n", token->cmd, token->inputfile, token->have_in, token->outputfile, token->have_out, count_file(token->file_head));
	return (0);
}

int	exec_first_cmd(char **args, t_minishell *ms)
{
	t_token *token;
	char	*path;
	char	**env;
	
	ft_putstr_fd("FIRST\n", 2);
	token = ms->t_head;
	if (token->next)
	{
		if (pipe(token->pipefd))
			strerror(errno);
	}
	env = env_to_tab(ms);
	path = make_path(token, ms);
	token->pid = fork();
	if (token->pid == -1)
		return (2);
	if (token->pid == 0)
	{
		if (init_execute(token, ms))
			return (1);
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
		//close(last->pipefd[0]);
		// close(last->pipefd[1]);
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

	if (token->pid == 0)
	{
		if (init_execute(token, ms))
			return (1);
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

	env = env_to_tab(ms);
	path = make_path(token, ms);
	token->pid = fork();
	if (token->pid == -1)
		return (2);
	if (token->pid == 0)
	{
		if (init_execute(token, ms))
			return (1);
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
			close(last->pipefd[0]);
		}
		if (token->have_out)
		{
			if (dup2(token->outputfile, 1) == -1)
				perror("minishell 13 :");
		}
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

	g_mode = 1;
	ms->path_absolute = get_path_env(ms);
	token = ms->t_head;
	args = args_to_tab(token, ms);
	exec_first_cmd(args, ms);
	
	last = token;
	if (token->next)
		token = token->next;
	else
	{
		token = ms->t_head;
		while (token)
		{
			waitpid(token->pid, NULL, 0);
			token = token->next;
		}	
		return (0);
	}
	while (token->next)
	{
		args = args_to_tab(token, ms);
		exec_middle(args, last, token, ms);
		close(last->pipefd[0]);
		close(last->pipefd[1]);
		last = token;
		token = token->next;
	}
	args = args_to_tab(token, ms);
	exec_last(args, last, token, ms);
	token = ms->t_head;
	close(last->pipefd[0]);
	close(last->pipefd[1]);
	while (token)
	{
		waitpid(token->pid, NULL, 0);
		token = token->next;
	}
	return (1);
}