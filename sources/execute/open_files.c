/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/31 12:24:07 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_have_next_type(t_file *file, int type)
{
	if (!file->next)
		return (1);
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

	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	signal(SIGINT, sigint_heredoc);
	append = readline(">");
	while (!ft_strcmp(append, limiter))
	{
		printf("fd = %d append = %s\n", fd, append);
		ft_putstr_fd(append, fd);
		ft_putstr_fd("\n", fd);
		free(append);
		append = readline(">");
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
	perror("");
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
		if (check_have_next_type(file, 1))
			return (fd);
		file = file->next;
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
		if (check_have_next_type(file, 0))
			return (fd);
		file = file->next;
	}
	return (fd);
}
