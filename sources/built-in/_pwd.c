/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 13:45:06 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token)
{
	char	v_print[50];

	if (count_arg(token->arg_head))
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(v_print, 50) == NULL)
	{
		strerror(errno);
		return (1);
	}
	if (*v_print)
	{
		ft_putstr_fd(v_print, 2);
		ft_putstr_fd("\n", 2);
	}
	return (EXIT_SUCCESS);
}
