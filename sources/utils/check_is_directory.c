/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/20 15:59:32 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print(char *msg, char *path, int printable)
{
	if (printable)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(msg, 2);
	}
}

int	check_is_directory(char *path, int printable)
{
	DIR	*dir;

	if (!path)
		return (1);
	if ((path[0] == '.' && path[1] == '\0'))
	{
		print(": filename argument required\n", path, printable);
		return (0);
	}
	if ((path[0] == '.' && path[1] == '.' && path[2] == '\0'))
	{
		print(": command not found\n", path, printable);
		return (0);
	}
	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		print(": Is a directory\n", path, printable);
		return (0);
	}
	return (1);
}
