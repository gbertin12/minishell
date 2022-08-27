/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:31:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 16:06:07 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*s;
	// t_token		*token;
	// t_arg		*arg;
	// t_file		*file;

	(void)argv;
	(void)argc;
	g_mode = 0;
	init_minishell(&ms);
	copy_env(&ms, envp);
	init_signals();
	while (1)
	{
		if (g_mode ==  5)
			g_mode = 0;
		s = readline(get_prompt(&ms, 2));
		if (!s || ft_strncmp("exit", s, 4) == 0)
			exit(0);
		if (parsing(s, &ms) != 0)
			continue ;
		expand(&ms);
		// token = ms.t_head;
		// while (token)
		// {
		// 	arg = token->arg_head;
		// 	printf("CMD = %s\n", token->cmd);
		// 	printf("ARG = ");
		// 	while (arg)
		// 	{
		// 		printf("%s | ", arg->value);
		// 		arg = arg->next;
		// 	}
		// 	printf("\n");
		// 	file = token->file_head;
		// 	printf("FILES = ");
		// 	while (file)
		// 	{
		// 		printf("%s[%d] %s | ", file->path, file->append, file->type == 1 ? "OUT" : "IN");
		// 		file = file->next;
		// 	}
		// 	printf("\n");
		// 	token = token->next;
		// }
		if (s && *s)
    		add_history(s);
		browse_cmd(&ms);
		g_mode = 0;
		free_tokens(&ms);
		ms.t_head = NULL;
		free(s);
	}
	if (s)
		free(s);
	free_all(&ms);
	return (EXIT_SUCCESS);
}
