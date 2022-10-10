/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:50:25 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/10 11:50:37 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	token_is_empty(t_token *t)
{
	if ((!t->cmd || !*t->cmd)
		&& (!t->arg_head || !*t->arg_head->value)
		&& (!t->file_head || !*t->file_head->path))
		return (1);
	return (0);
}
