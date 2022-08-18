/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:57:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 15:10:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_export(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	char	*key;
	char	*value;
	char	**tmp;

	if (token == NULL)
		return (EXIT_SUCCESS);
	arg = token->arg_head;
	while (arg != NULL)
	{
		if (ft_strchr(arg->value, '=') == NULL)
		{
			arg = arg->next;
			continue ;
		}
		tmp = ft_split(arg->value, '=', ms);
		key = tmp[0];
		value = ft_superjoin(tmp, ms);
		if (do_env_key_exist(key, ms))
			replace_env_value(key, value, ms);
		else
			add_env_key_value(key, value, ms);
		arg = arg->next;
		ft_free(tmp, ms);
	}
	return (EXIT_SUCCESS);
}
