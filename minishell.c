/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/15 18:34:37 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_env		*e;
	char		**s;
	size_t		i;

	(void)argv;
	(void)argc;
	ms.o_head = NULL;
	ms.e_head = NULL;
	copy_env(&ms, envp);
	s = env_to_tab(&ms);
	i = -1;
	while (s[++i])
		printf("%s\n", s[i]);
	e = ms.e_head;
	while (e != NULL)
	{
		free(e->key);
		free(e->value);
		e = e->next;
	}
	i = -1;
	while (s[++i])
		free(s[i]);
	free_all(&ms);
	return (EXIT_SUCCESS);
}
