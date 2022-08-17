/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/17 12:05:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*s;
	t_token		*token;
	t_arg		*arg;

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
		token = ms.t_head;
		while(token)
		{
			arg = token->arg_head;
			printf("CMD = %s\n", token->cmd);
			printf("ARG = ");
			while(arg)
			{
				printf("%s ", arg->value);
				arg = arg->next;
			}
			printf("\n");
			token = token->next;
		}
		free(s);
	}
	
	free(s);
	free_all(&ms);
	return (EXIT_SUCCESS);
}
