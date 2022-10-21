/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 09:23:44 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_heredoc(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by\
 end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	return (1);
}

static int	print_in_file(int fd, char *limiter, t_minishell *ms)
{
	char	*append;
	int		err;

	err = 0;
	rl_clear_history();
	signal(SIGINT, sigint_heredoc);
	append = readline("> ");
	while (!ft_strcmp(append, limiter))
	{
		append = heredoc_expand(append, ms);
		if (append)
		{
			ft_putstr_fd(append, fd);
			ft_putstr_fd("\n", fd);
		}
		else if (!append)
		{
			if (g_lretv != 130)
				err = error_heredoc(limiter);
			else 
				return (130);
			break ;
		}
		ft_free(append, ms);
		append = readline("> ");
	}
	ft_free(append, ms);
	return (err);
}

static void	heredoc_child(int fd, char *limiter, t_minishell *ms)
{
	int	ret;
	
	signal(SIGINT, sigint_heredoc);
	ret = print_in_file(fd, limiter, ms);
	close(fd);
	exit_child(ret, ms);
}

static int	set_ret_value(int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	signal(SIGQUIT, sigquit_exec);
	return (WEXITSTATUS(status));
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
	close(fd);
	if (set_ret_value(pid) == 130)
		return (-2);
	if (set_ret_value(pid) == 1)
		return (-3);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(tmp_file);
	return (fd);
}
