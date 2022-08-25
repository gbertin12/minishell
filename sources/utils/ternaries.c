/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternaries.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:39:18 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/25 12:13:41 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	char_ternary(char condition, char true, char false)
{
	if (condition)
		return (true);
	return (false);
}

char	*string_ternary(char condition, char *true, char *false)
{
	if (condition)
		return (true);
	return (false);
}

size_t	size_t_ternary(char condition, size_t a, size_t b)
{
	if (condition)
		return (a);
	return (b);
}
