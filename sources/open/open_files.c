/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 11:32:05 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_have_next_type(t_file *file, char type)
{
	while (file)
	{
		if (file->type == type)
			return (0);
		file = file->next;
	}
	return (1);
}

static int	open_output2(t_file *file, t_token *token, t_minishell *ms)
{
	int	fd;

	fd = 0;
	file->path = expand_file(file->path, file, ms);
	if (!file->path || !check_is_directory(file->path, 1))
		return (-1);
	if (file->append)
		fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		put_error_fd(file, token->file_head, ms);
	return (fd);
}

int	open_output(t_token *token, t_minishell *ms)
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
		fd = open_output2(file, token, ms);
		if (fd == -1)
			break ;
		file = file->next;
		if (check_have_next_type(file, 1))
			return (fd);
	}
	return (fd);
}

static int	open_input2(t_file *file, t_token *token, t_minishell *ms)
{
	int	fd;

	fd = 0;
	file->path = expand_file(file->path, file, ms);
	if (!file->path || !check_is_directory(file->path, 1))
		return (-1);
	if (file->append)
		fd = heredoc(file->path, ms);
	else
		fd = open(file->path, O_RDONLY);
	if (fd < 0)
		put_error_fd(file, token->file_head, ms);
	return (fd);
}

int	open_input(t_token *token, t_minishell *ms)
{
	int		fd;
	t_file	*file;

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
		fd = open_input2(file, token, ms);
		if (fd < 0)
			return (-1) ;
		file = file->next;
		if (check_have_next_type(file, 0))
			return (fd);
	}
	return (fd);
}
