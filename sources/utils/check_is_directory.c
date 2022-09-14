/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/14 09:09:38 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_directory(t_exec *exec, int printable)
{
	DIR	*dir;

	dir = opendir(exec->token->cmd);
	if (dir != NULL)
	{
		closedir(dir);
		if (printable)
			printf("minishell: %s: is a directory\n", exec->token->cmd);
		return (0);
	}
	return (1);
}
