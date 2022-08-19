/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 15:36:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(int fd)
{
	char	v_print[50];

	if (getcwd(v_print, 50) == NULL)
	{
		if (errno == ERANGE)
			perror("ERANGE");
		else if (errno == EFAULT)
			perror("EFAULT");
		else if (errno == EIO)
			perror("EIO");
		else if (errno == EACCES)
			perror("EACCES");
		return (EXIT_FAILURE);
	}
	if (*v_print)
	{
		ft_putstr_fd(v_print, fd);
		ft_putstr_fd("\n", fd);
	}
	return (EXIT_SUCCESS);
}
