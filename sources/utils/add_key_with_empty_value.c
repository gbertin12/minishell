/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_key_with_empty_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:58:13 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/20 10:22:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_key_with_empty_value(char *s, t_minishell *ms)
{
	if (check_key_env(s) || s[0] == '=')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\" not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	if (!do_env_key_exist(s, ms))
		add_env_key_value(s, NULL, ms);
	return (EXIT_SUCCESS);
}
