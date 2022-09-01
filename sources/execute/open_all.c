/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:59:54 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/01 13:26:57 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_all(t_minishell *ms)
{
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		token->inputfile = 0;
		token->outputfile = 0;
		token->have_in = have_infile(token);
		token->have_out = have_outfile(token);
		if (token->have_in)
			token->inputfile = open_input(token, ms);
		if (token->have_out)
			token->outputfile = open_output(token);
		token = token->next;	
	}
}
