/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:59:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 08:41:55 by gbertin          ###   ########.fr       */
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
		if (token->have_in)
		{
			token->inputfile = open_input(token, ms);
			if (token->inputfile < 0)
				break ;
	
		}
		if (token->have_out)
			token->outputfile = open_output(token, ms);
		token = token->next;
	}
	print_err(ms);
}
