// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   browse_cmd.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/08/22 14:47:47 by gbertin           #+#    #+#             */
// /*   Updated: 2022/08/23 16:03:57 by gbertin          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// char	**get_path_env(t_minishell *ms)
// {
// 	char	**all_path;
// 	char	**env;
// 	size_t	i;

// 	i = 0;
// 	env = env_to_tab(ms);
// 	if (!env)
// 		return (NULL);
// 	while (env[i])
// 	{
// 		if (ft_strncmp("PATH", env[i], 4) == 0)
// 		{
// 			while (*env[i] != '/' && *env[i] != '\0')
// 				env[i]++;
// 			all_path = ft_split(env[i], ':', ms);
// 			if (!all_path)
// 				return (NULL);
// 			return (all_path);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// int	ft_search_char(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '/')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*make_path(t_token *token, t_minishell *ms)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*path;

// 	i = 0;
// 	if (ms->path_absolute == NULL || ft_search_char(token->cmd))
// 	{
// 		if (access(token->cmd, 0) == 0)
// 			return (ft_strdup(token->cmd, ms));
// 		return (NULL);
// 	}
// 	while (ms->path_absolute[i] != NULL)
// 	{
// 		tmp = ft_strjoin(ms->path_absolute[i], "/", ms);
// 		path = ft_strjoin(tmp, token->cmd, ms);
// 		if (access(path, 0) == 0)
// 			return (path);
// 		i++;
// 	}
// 	return (NULL);
// }

// int		init_execute(t_token *token, t_minishell *ms)
// {
// 	token->have_in = have_infile(token);
// 	token->have_out = have_outfile(token);
// 	if (token->have_in)
// 		token->inputfile = open_input(token, ms);
// 	if (token->have_out)
// 		token->outputfile = open_output(token);
// 	printf("%s fd in = %d have in = %d fd out = %d have out = %d NBFILE = %zu\n", token->cmd, token->inputfile, token->have_in, token->outputfile, token->have_out, count_file(token->file_head));
// 	return (0);
// }

// int	redir_in(t_token *token, int pipefd[2])
// {
// 	if (token->have_in && token->inputfile > 0)
// 	{
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		if (dup2(token->inputfile, 0) == -1)
// 			return (1);
// 		close(token->inputfile);
// 	}
// 	return (0);
// }

// int	redir_out(t_token *token, int pipefd[2])
// {
// 	if (token->have_out && token->outputfile > 0)
// 	{
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		if (dup2(token->outputfile, 1) == -1)
// 			return (1);
// 		close(token->outputfile);
// 		return (0);
// 	}
// 	else if (token->next)
// 	{
// 		close(pipefd[0]);
// 		if (dup2(pipefd[1], 1) == - 1)
// 			return (1);
// 	}
// 	return (0);
// }

// int	redir_pipein(t_token *token, int pipefd[2])
// {
// 	if (!token->have_in)
// 	{
// 		close(pipefd[1]);
// 		if (dup2(pipefd[0], 0) == -1)
// 			return (1);
// 	}
// 	else
// 	{
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 	}
// 	return (0);
// }

// int	execute_cmd(t_token *token, int pipefd[2], char **args, t_minishell *ms)
// {
// 	char	*path;
// 	char	**env;
	
// 	env = env_to_tab(ms);
// 	path = make_path(token, ms);
// 	if (!path)
// 		return (1);
// 	token->pid = fork();
// 	if (init_execute(token, ms))
// 		return (1);
// 	if (token->pid == -1)
// 		return (2);
// 	if (token->pid == 0)
// 	{
// 		printf("IN CHILD \n\n");
// 		if (redir_in(token, pipefd))
// 			strerror(errno);
// 		if (redir_out(token, pipefd))
// 			strerror(errno);
// 		if (path)
// 			execve(path, args, env);
// 		strerror(errno);
// 		exit (1);
// 	}
// 	else
// 	{
// 		if (redir_pipein(token, pipefd))
// 			return (1);
// 	}
// 	return (0);
// }

// int	browse_cmd(t_minishell *ms)
// {
// 	t_token	*token;
// 	int		pipefd[2];
// 	char	**args;

// 	g_mode = 1;
// 	ms->path_absolute = get_path_env(ms);
// 	token = ms->t_head;
// 	while (token)
// 	{
// 		args = args_to_tab(token, ms);
// 		if (token->next)
// 		{
// 			if (!pipe(pipefd))
// 			{
// 				strerror(errno);
// 				token = token->next;
// 				continue ;
// 			}
// 		}
// 		if (execute_cmd(token, pipefd, args, ms) == 2)
// 		{
// 			ft_putstr_fd("AFTER EXEC : ", 2);
// 			strerror(errno);
// 		}
// 		token = token->next;
// 	}
// 	token = ms->t_head;
// 	while (token)
// 	{
// 		waitpid(token->pid, NULL, 0);
// 		token = token->next;
// 	}
// 	return (1);
// }