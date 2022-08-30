/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_key_with_empty_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:58:13 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/30 09:58:58 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_key_with_empty_value(char *s, t_minishell *ms)
{
	if (do_env_key_exist(s, ms))
		replace_env_value(s, NULL, ms);
	else
		add_env_key_value(s, NULL, ms);
}
