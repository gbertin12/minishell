/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/17 13:18:25 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_heredoc(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by\
 end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

static void	print_in_file(int fd, char *limiter, t_minishell *ms)
{
	char	*append;

	rl_clear_history();
	signal(SIGINT, sigint_heredoc);
	append = readline(">");
	while (!ft_strcmp(append, limiter))
	{
		append = heredoc_expand(append, ms);
		if (append && *append)
		{
			ft_putstr_fd(append, fd);
			ft_putstr_fd("\n", fd);
		}
		else if (!append)
		{
			error_heredoc(limiter);
			break ;
		}
		ft_free(append, ms);
		append = readline("> ");
	}
	ft_free(append, ms);
}

static void	heredoc_child(int fd, char *limiter, t_minishell *ms)
{
	signal(SIGINT, sigint_heredoc);
	print_in_file(fd, limiter, ms);
	close(fd);
	exit_child(0, ms);
}

int	heredoc(char *limiter, t_minishell *ms)
{
	int		fd;
	int		pid;
	char	*tmp_file;

	tmp_file = ft_strjoin("/tmp/", ft_itoa(*limiter, ms), ms);
	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (fd);
	signal(SIGQUIT, sigquit_handler);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		heredoc_child(fd, limiter, ms);
	waitpid(pid, NULL, 0);
	signal(SIGQUIT, sigquit_exec);
	close(fd);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(tmp_file);
	return (fd);
}
