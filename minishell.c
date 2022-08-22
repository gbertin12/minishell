/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 14:37:21 by gbertin          ###   ########.fr       */
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
	t_file		*file;

	(void)argv;
	(void)argc;
	g_mode = 0;
	//ft_bzero(&ms, sizeof(t_minishell));
	init_minishell(&ms);
	copy_env(&ms, envp);
	init_signals();
	while (1)
	{
		s = readline("\033[031m┌──\033[034m(\033[032mminishell\033[034m)\n\033[031m└─\033[032m$ \033[034m");
		if (!s || ft_strncmp("exit", s, 4) == 0)
			break ;
		if (parsing(s, &ms) != 0)
			continue ;
		expand(&ms);
		token = ms.t_head;
		while (token)
		{
			arg = token->arg_head;
			printf("CMD = %s apos = %d\n", token->cmd, token->apos);
			printf("ARG = ");
			while (arg)
			{
				printf("%s | ", arg->value);
				arg = arg->next;
			}
			printf("\n");
			file = token->file_head;
			printf("FILES = ");
			while (file)
			{
				printf("%s[%d] %s | ", file->path, file->append, file->type == 1 ? "OUT" : "IN");
				file = file->next;
			}
			printf("\n");
			token = token->next;
		}
		if (s && *s)
    		add_history(s);
		// if (ms.t_head->cmd == "echo")
		// {
		// 	printf("here\n");
		// 	_echo(ms.t_head);
		// }
		free_tokens(&ms);
		ms.t_head = NULL;
		free(s);
	}
	free_all(&ms);
	return (EXIT_SUCCESS);
}

// token = ms.t_head;
// 		while (token)
// 		{
// 			arg = token->arg_head;
// 			printf("CMD = %s\n", token->cmd);
// 			printf("ARG = ");
// 			while (arg)
// 			{
// 				printf("%s | ", arg->value);
// 				arg = arg->next;
// 			}
// 			printf("\n");
// 			file = token->input_head;
// 			printf("INFILE = ");
// 			while (file)
// 			{
// 				printf("%s[%d] | ", file->path, file->append);
// 				file = file->next;
// 			}
// 			printf("\n");
// 			file = token->output_head;
// 			printf("OUTFILE = ");
// 			while (file)
// 			{
// 				printf("%s[%d] | ", file->path, file->append);
// 				file = file->next;
// 			}
// 			printf("\n");
// 			token = token->next;
// 		}
