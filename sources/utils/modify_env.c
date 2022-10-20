/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:53:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/20 14:54:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modify_env(char *key, char *value, t_minishell *ms)
{
	if (!value)
		add_key_with_empty_value(key, ms);
	else if (do_env_key_exist(key, ms))
		replace_env_value(key, value, ms);
	else
		add_env_key_value(key, value, ms);
}
