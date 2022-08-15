/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:55:39 by ccambium          #+#    #+#             */
/*   Updated: 2021/12/06 16:16:43 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((!src && !dest) || n == 0)
		return (dest);
	if (dest <= src)
	{
		i = 0;
		while (i < n)
		{
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
			i++;
		}
		return (dest);
	}
	i = n;
	while (i > 0)
	{
		*((unsigned char *) dest + i - 1) = *((unsigned char *)src + i - 1);
		i--;
	}
	return (dest);
}
