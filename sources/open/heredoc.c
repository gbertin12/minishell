/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 12:49:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_ret_value(int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	signal(SIGQUIT, sigquit_exec);
	return (WEXITSTATUS(status));
}

static int	heredoc2(int fd, int pid, char *tmp_file, t_minishell *ms)
{
	if (set_ret_value(pid) == 130)
		return (ft_free(tmp_file, ms), -2);
	if (set_ret_value(pid) == 1)
		return (ft_free(tmp_file, ms), -3);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (ft_free(tmp_file, ms), -1);
	unlink(tmp_file);
	return (ft_free(tmp_file, ms), fd);
}

int	heredoc(char *limiter, t_minishell *ms)
{
	int		fd;
	int		pid;
	char	*tmp_file;

	pid = 0;
	tmp_file = ft_strjoin("/tmp/", ft_itoa(*limiter, ms), ms);
	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (ft_free(tmp_file, ms), fd);
	signal(SIGQUIT, sigquit_handler);
	pid = fork();
	if (pid < 0)
		return (ft_free(tmp_file, ms), -1);
	if (pid == 0)
		heredoc_child(fd, limiter, ms);
	return (heredoc2(fd, pid, tmp_file, ms));
}
