/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:59:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 16:54:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err(t_minishell *ms)
{
	t_file_error	*err;

	err = ms->err_head;
	if (err && err->err)
	{	
		while (err)
		{
			ft_putstr_fd(err->err, 2);
			err = err->next;
		}
	}
}

int	open_output(t_file *file, t_token *token, t_minishell *ms)
{
	int	fd;

	fd = 0;
	if (file->append)
		fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		put_error_fd(file, token->file_head, ms);
	return (fd);
}

int	open_input(t_file *file, t_token *token, t_minishell *ms)
{
	int	fd;

	fd = 0;
	if (file->append)
		fd = heredoc(file->path, ms);
	else
		fd = open(file->path, O_RDONLY);
	if (fd < -1)
		return (fd);
	else if (fd < 0)
		put_error_fd(file, token->file_head, ms);
	return (fd);
}

static void	open_file(t_token *token, t_minishell *ms)
{
	t_file	*file;

	file = token->file_head;
	while (file)
	{
		file->path = expand_file(file->path, ms);
		if (!file->path)
		{
			if (file->type == 0)
				token->inputfile = -1;
			else if (file->type == 1)
				token->outputfile = -1;
		}
		else
		{
			if (file->type == 0)
				token->inputfile = open_input(file, token, ms);
			else if (file->type == 1)
				token->outputfile = open_output(file, token, ms);
		}
		if (token->inputfile < 0 || token->outputfile < 0)
			return ;
		file = file->next;
	}
}

void	open_all(t_minishell *ms)
{
	t_token			*token;

	ms->err_head = NULL;
	token = ms->t_head;
	while (token)
	{
		token->inputfile = 0;
		token->outputfile = 0;
		token->have_in = have_infile(token);
		token->have_out = have_outfile(token);
		open_file(token, ms);
		token = token->next;
	}
	print_err(ms);
}
