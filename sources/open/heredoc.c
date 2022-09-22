/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/22 15:28:27 by ccambium         ###   ########.fr       */
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
		free(append);
		append = readline(">");
	}
	free(append);
}

int	heredoc(char *limiter, t_minishell *ms)
{
	int		fd;
	int		pid;

	fd = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	g_mode = 1;
	if (pid == 0)
	{
		print_in_file(fd, limiter, ms);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	g_mode = 0;
	close(fd);
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	return (fd);
}
