/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternaries.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:39:18 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/23 09:59:14 by ccambium         ###   ########.fr       */
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
