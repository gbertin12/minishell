/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/16 11:24:06 by ccambium         ###   ########.fr       */
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
	t_token		*t;

	ms.o_head = NULL;
	ms.e_head = NULL;
	t = ft_malloc(sizeof(t_token), &ms);
	t->arg_head = ft_malloc(sizeof(t_arg), &ms);
	t->arg_head->next = NULL;
	t->arg_head->value = "L=miam";
	(void)argv;
	(void)argc;
	copy_env(&ms, envp);
	_export(t, &ms);
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
