/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/19 12:01:39 by ccambium         ###   ########.fr       */
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
	init_signals();
	//ft_bzero(&ms, sizeof(t_minishell));
	init_minishell(&ms);
	token = ft_malloc(sizeof(token), &ms);
	arg = ft_malloc(sizeof(arg), &ms);
	file = ft_malloc(sizeof(file), &ms);
	ft_memset(token, 0, sizeof(t_token));
	ft_memset(arg, 0, sizeof(t_arg));
	token->arg_head = arg;
	copy_env(&ms, envp);
	while (1)
	{
		s = readline("\033[34mminishell ➤ \033[32m");
		if (s == NULL)
			break ;
		if (ft_strncmp("exit", s, 4) == 0)
			break ;
		parsing(s, &ms);
		expand(&ms);
		token = ms.t_head;
		while (token)
		{
			arg = token->arg_head;
			printf("CMD = %s\n", token->cmd);
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
    		add_history (s);
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
