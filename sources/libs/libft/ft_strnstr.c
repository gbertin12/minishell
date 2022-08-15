/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 06:53:10 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/31 06:53:10 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (i < len && *(haystack + i))
	{
		if (*(needle + l) == *(haystack + i))
			l++;
		else if (*(needle + l) == 0)
			return ((char *)haystack + i - l);
		else
		{
			i = i - l;
			l = 0;
		}
		i++;
	}
	if (*(needle + l) == 0 && i <= len)
		return ((char *)haystack + i - l);
	return (NULL);
}
