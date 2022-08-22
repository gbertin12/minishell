/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 09:38:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token)
{
	char	v_print[50];
	int		fd;
	int		check_f;

	check_f = check_files(token);
	if (check_f)
		return (1);
	fd = open_output(token);
	if (fd < 0)
		return (fd);
	if (getcwd(v_print, 50) == NULL)
		strerror(errno);
	if (*v_print)
	{
		ft_putstr_fd(v_print, fd);
		ft_putstr_fd("\n", fd);
	}
	return (EXIT_SUCCESS);
}
