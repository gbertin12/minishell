/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/23 22:54:45 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	}
	return (fd);
}

int	open_input(t_token *token, t_minishell *ms)
{
	t_file	*file;
	int		fd;
	int i;

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
			fd = open(".tmp", O_RDWR | O_CREAT | O_APPEND, 0644);
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
	}
	return (fd);
}
