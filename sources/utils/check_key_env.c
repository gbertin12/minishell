/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:19:46 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/20 08:56:35 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_key_env(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (1);
	while (s[++i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (1);
	}
	if (s && s[0] == '\0')
		return (1);
	return (0);
}
