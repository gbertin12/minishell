/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 12:28:13 by ccambium         ###   ########.fr       */
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
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
			fd = open(file->path, O_WRONLY | O_CREAT, 0644);
		else
			fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("file not found or permission denied\n", 2);
			return (1);
		}
		file = file->next;
	}
	return (fd);
}
