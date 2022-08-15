/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:30:42 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/29 07:30:58 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) != 0 && i < size - 1 && size != 0)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (size != 0)
		*(dst + i) = 0;
	while (*(src + i) != 0)
		i++;
	return (i);
}
