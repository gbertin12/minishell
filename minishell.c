/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/16 21:12:09 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_env		*e;

	ms.o_head = NULL;
	ms.e_head = NULL;
	(void)argv;
	(void)argc;
	copy_env(&ms, envp);
	_pwd();
	e = ms.e_head;
	while (e != NULL)
	{
		free(e->key);
		free(e->value);
		e = e->next;
	}
	free_all(&ms);
	return (EXIT_SUCCESS);
}
