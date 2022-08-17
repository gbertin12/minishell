/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 09:00:55 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/31 09:00:55 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_minishell *ms)
{
	size_t	len;
	size_t	i;
	char	*v;

	i = 0;
	len = ft_strlen(s);
	v = ft_malloc(len + 1, ms);
	if (v == NULL)
		return (NULL);
	while (i < len)
	{
		*(v + i) = *(s + i);
		i++;
	}
	*(v + i) = 0;
	return (v);
}
