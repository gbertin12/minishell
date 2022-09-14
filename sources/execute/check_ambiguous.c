/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:18:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/14 19:18:54 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ambiguous(char *path, char *print, t_minishell *ms)
{
	char	**split;
	int		flag;

	flag = 0;
	if (path && path[0] != '\0')
	{
		split = ft_split_set(path, " \n\r\v\t\f", ms);
		if (!split)
			return (1);
		if (split[1])
			flag = 1;
	}
	if (!path || flag || path[0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}
