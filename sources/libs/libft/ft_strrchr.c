/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 05:43:07 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/30 05:43:07 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i != 0)
	{
		if (c % 256 == *(s + i))
			return ((char *)s + i);
		i--;
	}
	if (*(s + 0) == c % 256)
		return ((char *)s);
	return (NULL);
}
