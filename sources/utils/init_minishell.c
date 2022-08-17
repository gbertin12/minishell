/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:27:00 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 04:32:00 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_minishell(t_minishell *ms)
{
	ms->e_head = NULL;
	ms->o_head = NULL;
	ms->t_head = NULL;
	ms->l_retv = 0;
	ms->l_input = NULL;
}
