/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:29:40 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 12:22:20 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_files(t_token *token)
{
	t_file	*file;

	file = token->file_head;
	while (file)
	{
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		if (access(file->path, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (0);
		}
		file = file->next;
	}
	return (1);
}
