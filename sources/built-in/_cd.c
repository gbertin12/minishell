/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:56:23 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 12:33:24 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char exec_chdir(char *path)
{
	if(chdir(path) == -1)
	{
		//print error
		return (0);
	}
	return (1);
}

char	_cd(t_token *token)
{
	size_t	nb_arg;

	nb_arg = count_arg(token->arg_head);
	if (nb_arg > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (0);
	}
	if (nb_arg == 0)
		return (1);
	return(exec_chdir(token->arg_head->value));
}
