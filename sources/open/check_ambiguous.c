/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:18:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/17 09:26:12 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ambiguous(char *path, char *print, t_file *file, int ambiguous)
{
	if ((!path || path[0] == '\0') && !ft_strchr(print, '$'))
		return (1);
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
