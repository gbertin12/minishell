/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/17 09:38:41 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_env		*e;
	char		*s;

	(void)argv;
	(void)argc;
	init_minishell(&ms);
	copy_env(&ms, envp);
	while (1)
	{
		s = readline("\033[30mminishell ➤ \033[32m");
		if (ft_strncmp("exit", s, 4) == 0)
			break ;
		parsing(s, &ms);
		free(s);
	}
	free(s);
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
