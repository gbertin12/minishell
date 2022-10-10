/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:45:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 16:23:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_child(int num_err, t_minishell *ms)
{
	if (ms->exec->tmpin)
		close(ms->exec->tmpin);
	if (ms->exec->tmpout)	
		close(ms->exec->tmpout);
	free(ms->s);
	free_all(ms);
	exit(num_err);
}
