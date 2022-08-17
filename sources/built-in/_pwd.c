/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/17 10:30:07 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(void)
{
	char	v_print[50];

	if (getcwd(v_print, 50) == NULL)
	{
		ft_putstr_fd("Cannot get cwd path\n", 2);
		if (errno == ERANGE)
			ft_putstr_fd("Buffer size is too small", 2);
		else if (errno == EFAULT)
			ft_putstr_fd("Invalide pointer on buffer", 2);
		else if (errno == EIO)
			ft_putstr_fd("I/O error", 2);
		else if (errno == EACCES)
			ft_putstr_fd("You don't have access for this folder", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(v_print, 0);
	return (EXIT_SUCCESS);
}
