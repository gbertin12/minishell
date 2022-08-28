/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_next_sep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:15:55 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/28 12:15:20 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	search_next_sep(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '|' && s[i] != '>' && s[i] != '<'
		&& !ft_isalnum(s[i]) && s[i] != '\0' && !is_space(s[i]))
		i++;
	return (i);
}
