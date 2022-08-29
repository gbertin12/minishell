/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:19:46 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 11:14:21 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_key_env(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (1);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_putchar_fd(s[i], 2);
			ft_putstr_fd("   IN ISALNUM\n", 2);
			
			return (1);
		}
		i++;
	}
	return (0);
}
