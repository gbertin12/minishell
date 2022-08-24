// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   browse_cmd3.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/08/24 11:06:58 by gbertin           #+#    #+#             */
// /*   Updated: 2022/08/24 12:56:17 by gbertin          ###   ########.fr       */
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

// void	init(int cmd_id, t_token *token, t_minishell *ms)
// {
// 	int		nb_cmd;
	
// 	ms->tmpin = dup(0);
// 	ms->tmpout = dup(1);
// 	nb_cmd = count_token(token);
// 	if (nb_cmd == cmd_id && nb_cmd != 1)
// 		token->status = 2;
// 	else if (cmd_id != 1 && cmd_id < nb_cmd)
// 		token->status = 1;
// 	if (token->status == 1 || (token->status == 0 && token->next))
// 	{
// 		if (pipe(token->pipefd))
// 			perror("minishell 1 ");
// 	}
// 	token->have_in = have_infile(token);
// 	token->have_out = have_outfile(token);
// }

// int	execute(int id_cmd, t_token *last, t_token *token, t_minishell *ms)
// {
// 	char	**args;
// 	int		in;
// 	int		out;
// 	char	**env;
// 	char	*path;

// 	//args = args_to_tab(token, ms);
// 	env = env_to_tab(ms);
// 	path = make_path(token, ms);
// 	init(id_cmd, token, ms);
// 	in = ms->tmpin;
// 	out = ms->tmpout;
// 	if (token->have_in)
// 		in = open_input(token, ms);
// 	else if (!token->have_in && token->status != 0)
// 	{
// 		in = dup(last->pipefd[0]);
// 		close(token->pipefd[1]);
// 	}
// 	dup2(in, 0);
// 	close(in);
// 	if (token->have_out)
// 		out = open_output(token);
// 	else if (token->status != 2 && count_token(token) != 1)
// 	{
// 		out = token->pipefd[1];
// 		close(token->pipefd[0]);
// 	}
// 	dup2(out, 1);
// 	close(out);
// 	token->pid = fork();
// 	if (token->pid == 0)
// 	{
// 		execve(path, args, env);
// 		perror("minishell 2 ");
// 		exit(1);
// 	}
// 	return (0);
// }

// int	browse_cmd(t_minishell *ms)
// {
// 	t_token	*token;
// 	t_token	*last;
// 	int		cmd_id;

// 	cmd_id = 1;
// 	last = NULL;
// 	token = ms->t_head;
// 	while (token)
// 	{
// 		execute(cmd_id, last, token, ms);
// 		dup2(ms->tmpin, 0);
// 		dup2(ms->tmpout, 1);
// 		close(ms->tmpin);
// 		close(ms->tmpout);
// 		if (last)
// 		{
// 			if (last->pipefd[0])
// 				close(last->pipefd[0]);
// 			if (last->pipefd[0])
// 				close(last->pipefd[0]);
// 		}
// 		last = token;
// 		token = token->next;
// 		cmd_id += 1;
// 	}
// 	return (0);
// }
