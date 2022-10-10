/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:45:11 by gbertin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/10 16:23:49 by gbertin          ###   ########.fr       */
=======
/*   Updated: 2022/10/10 16:02:36 by ccambium         ###   ########.fr       */
>>>>>>> f775a1edb2b7ae412141bc597c085993b9f4f381
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
	rl_clear_history();
	exit(num_err);
}
