/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:18:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/16 09:26:27 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ambiguous(char *path, char *print, int ambiguous)
{
	if (!path || ambiguous || path[0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}
