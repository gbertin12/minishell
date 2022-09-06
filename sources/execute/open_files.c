/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/06 15:32:14 by ccambium         ###   ########.fr       */
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

static char	did_print(t_file *file, t_file *head)
{
	t_file *f;

	f = head;
	while (f && f != file)
	{
		if (!ft_strncmp(f->path, file->path, ft_strlen(f->path)))
			return (1);
		f = f->next;
	}
	return (0);
}

static void	put_error_fd(t_file *file, t_file *head)
{
	if (did_print(file, head))
		return ;
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
			put_error_fd(file, token->file_head);
		if (check_have_next_type(file, 1))
			return (fd);
		file = file->next;
	}
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
		if (file->append)
			fd = heredoc(file->path, ms);
		else
			fd = open(file->path, O_RDONLY);
		if (fd < 0)
			put_error_fd(file, token->file_head);
		if (check_have_next_type(file, 0))
			return (fd);
		file = file->next;
	}
	return (fd);
}
