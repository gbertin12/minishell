/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:36:06 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/08 17:36:06 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), t_minishell *ms)
{
	unsigned int	i;
	char			*v;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s) + 1;
	v = ft_malloc(len, ms);
	if (v == NULL)
		return (NULL);
	while (i < len - 1)
	{
		*(v + i) = f(i, *(s + i));
		i++;
	}
	*(v + i) = 0;
	return (v);
}
