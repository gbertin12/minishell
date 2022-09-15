/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/14 20:21:29 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_have_next_type(t_file *file, char type)
{
	while (file)
	{
		if (file->type == type)
			return (0);
		file = file->next;
	}
	return (1);
}

static char	did_print(t_file *file, t_file *head)
{
	t_file	*f;

	f = head;
	while (f && f != file)
	{
		if (!ft_strncmp(f->path, file->path, ft_strlen(f->path)))
			return (1);
		f = f->next;
	}
	return (0);
}

static void	put_error_fd(t_file *file, t_file *head, t_minishell *ms)
{
	t_file_error	*new_err;

	if (did_print(file, head))
		return ;
	if (ms->err_head == NULL)
	{
		new_err = ft_malloc(sizeof(t_file_error), ms);
		ms->err_head = new_err;
	}
	else
	{
		new_err = ft_malloc(sizeof(t_file_error), ms);
		add_end_err(ms->err_head, new_err);
	}
	new_err->next = NULL;
	new_err->err = ft_strjoin("minishell: ", file->path, ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, ": ", ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, strerror(errno), ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, "\n", ms);
}

static int	open_output2(t_file *file, t_token *token, t_minishell *ms)
{
	int	fd;

	fd = 0;
	if (ft_strchr(file->path, '$'))
	{
		file->path = expand_file(file->path, ms);
		if (!file->path)
			return (-1);
	}
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
	if (ft_strchr(file->path, '$'))
	{
		file->path = expand_file(file->path, ms);
		if (!file->path)
			return (-1);
	}
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
		file = file->next;
		if (check_have_next_type(file, 0))
			return (fd);
	}
	return (fd);
}
