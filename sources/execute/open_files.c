/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 10:55:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_have_next_type(t_file *file, int type)
{
	while (file)
	{
		if (file->type == type)
			return (0);
		file = file->next;
	}
	return (1);
}

int	heredoc(char *limiter)
{
	char	*append;
	int		fd;

	ft_putstr_fd(limiter, 2);
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	signal(SIGINT, sigint_heredoc);
	append = readline("heredoc>");
	while (!ft_strcmp(append, limiter))
	{
		ft_putstr_fd(append, fd);
		free(append);
		append = readline("heredoc>");
	}
	free(append);
	unlink(".tmp");
	return (fd);
}

static void	put_error_fd(t_file *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": ", 2);
	strerror(errno);
	ft_putchar_fd('\n', 2);
}

int	open_output(t_token *token)
{
	t_file	*file;
	int		fd;

	file = token->file_head;
	fd = 1;
	while (file)
	{
		if (fd > 0 && fd != 1)
			close(fd);
		if (!file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
			fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			put_error_fd(file);
		file = file->next;
		if (check_have_next_type(file, 1))
			return (fd);
	}
	return (fd);
}

int	open_input(t_token *token)
{
	t_file	*file;
	int		fd;

	file = token->file_head;
	fd = 1;
	while (file)
	{
		if (fd > 0 && fd != 1)
			close(fd);
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
			fd = heredoc(file->path);
		else
			fd = open(file->path, O_RDONLY, 0644);
		if (fd < 0)
			put_error_fd(file);
		file = file->next;
		if (check_have_next_type(file, 0))
			return (fd);
	}
	return (fd);
}
