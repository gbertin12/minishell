/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:09:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/07 10:09:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_files(t_file *head, t_minishell *ms)
{
	t_file	*file;
	t_file	*tmp;

	file = head;
	while (file)
	{
		tmp = file->next;
		ft_free(file->path, ms);
		ft_free(file, ms);
		file = tmp;
	}
}

static void	free_args(t_arg *head, t_minishell *ms)
{
	t_arg	*arg;
	t_arg	*tmp;

	arg = head;
	while (arg)
	{
		tmp = arg->next;
		ft_free(arg->value, ms);
		ft_free(arg, ms);
		arg = tmp;
	}
}

void	free_tokens(t_minishell *ms)
{
	t_token	*tmp;
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		if (token->inputfile)
			close (token->inputfile);
		if (token->outputfile)
			close (token->outputfile);
		free_files(token->file_head, ms);
		free_args(token->arg_head, ms);
		ft_free(token->cmd, ms);
		tmp = token->next;
		ft_free(token, ms);
		token = tmp;
	}
}
