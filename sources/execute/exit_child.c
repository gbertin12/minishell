/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:45:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/28 09:26:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_child(int num_err, t_minishell *ms)
{
	if (ms->exec)
	{
		close(ms->exec->tmpin);
		close(ms->exec->tmpout);
	}
	if (ms->s && ms->tester == 0)
		free(ms->s);
	free_all(ms);
	rl_clear_history();
	exit(num_err);
}
