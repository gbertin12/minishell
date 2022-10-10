/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 09:08:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_directory(char *path, int printable)
{
	DIR	*dir;

	if (!path)
		return (1);
	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		if (printable)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		return (0);
	}
	return (1);
}
