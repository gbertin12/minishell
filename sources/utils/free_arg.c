/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:29:03 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/03 13:31:26 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_arg(t_arg *arg, t_minishell *ms)
{
	if (arg->value)
		ft_free(arg->value, ms);
	ft_free(arg, ms);
}
