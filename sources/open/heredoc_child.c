/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:35:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/03 11:20:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_heredoc(char *limiter, int fd)
{
	ft_putstr_fd("minishell: warning: here-document delimited by\
 end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	return (fd);
}

static int	print_in_file(int fd, char *limiter, t_minishell *ms)
{
	char	*append;
	int		err;

	err = 0;
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
			err = 130;
			if (g_lretv != 130)
				err = error_heredoc(limiter, fd);
			break ;
		}
		free(append);
		append = readline("> ");
	}
	free(append);
	return (err);
}

void	heredoc_child(int fd, char *limiter, t_minishell *ms)
{
	int	ret;

	signal(SIGINT, sigint_heredoc);
	rl_clear_history();
	g_lretv = 0;
	ret = print_in_file(fd, limiter, ms);
	close(fd);
	exit_child(ret, ms);
}
