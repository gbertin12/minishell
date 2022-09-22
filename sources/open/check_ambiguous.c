/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:18:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/22 11:27:35 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ambiguous(char *path, char *print, t_file *file, int ambiguous)
{
	if (!path || ambiguous || path[0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (0);
	}
	if (check_have_next_type(file, 0))
		check_is_directory(path, 1);
	else
		check_is_directory(path, 0);
	return (1);
}
