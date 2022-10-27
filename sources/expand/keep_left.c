/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:37:43 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/28 00:34:25 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_of_key(char *w)
{
	size_t	i;

	i = 0;
	if (w[i] == '?')
		return (1);
	if ((!ft_isalpha(w[i]) && w[i] != '_') || !*w)
		return (i);
	while (w[i] && (ft_isalnum(w[i]) || w[i] == '_'))
		i++;
	return (i);
}

char	*keep_left(t_arg *arg, char *w, t_minishell *ms)
{
	char	*left;
	size_t	x;

	x = size_of_key((w + 1)) + 1;
	left = ft_substr(arg->value, (size_t)((w + x) - arg->value), ft_strlen((w + x)), ms);
	if (!left)
		return (NULL);
	return (left);
}
