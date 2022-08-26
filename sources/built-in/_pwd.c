/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:00:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 13:03:44 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd(t_token *token)
{
	char	v_print[50];

	if (getcwd(v_print, 50) == NULL)
	{
		strerror(errno);
		return (1);
	}
	if (*v_print)
		printf("%s\n", v_print);
	return (EXIT_SUCCESS);
}
