/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 16:19:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_in_file(int fd, char *limiter, t_minishell *ms)
{
	char	*append;

	signal(SIGINT, sigint_heredoc);
	append = readline(">");
	while (!ft_strcmp(append, limiter))
	{
		append = heredoc_expand(append, ms);
		ft_putstr_fd(append, fd);
		ft_putstr_fd("\n", fd);
		ft_free(append, ms);
		append = readline("> ");
	}
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
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		heredoc_child(fd, limiter, ms);
	waitpid(pid, NULL, 0);
	close(fd);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(tmp_file);
	return (fd);
}
