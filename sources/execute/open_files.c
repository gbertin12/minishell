/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 12:23:54 by gbertin          ###   ########.fr       */
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

	g_mode = 1;
	ft_putstr_fd(limiter, 2);
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	append = readline("heredoc>");
	while (!ft_strcmp(append, limiter))
	{
		ft_putstr_fd(append, fd);
		free(append);
		append = readline("heredoc>");
	}
	free(append);
	g_mode = 0;
	return (fd);
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
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			strerror(errno);
			ft_putchar_fd('\n', 2);
		}
		file = file->next;
		if (check_have_next_type(file, 1))
			return (fd);
	}
	return (fd);
}

int	open_input(t_token *token, t_minishell *ms)
{
	t_file	*file;
	int		fd;
	int		i;

	i = 0;
	file = token->file_head;
	fd = 1;
	while (file)
	{
		i++;
		if (fd > 0 && fd != 1)
			close(fd);
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
		{
			fd = heredoc(file->path);
			unlink(".tmp");
		}
		else
			fd = open(file->path, O_RDONLY, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("NB FILE ", 2);
			ft_putstr_fd(ft_itoa(i, ms), 2);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			strerror(errno);
		}
		file = file->next;
		if (check_have_next_type(file, 0))
			return (fd);
	}
	return (fd);
}
