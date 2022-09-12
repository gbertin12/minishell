/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:32:18 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/01 08:32:18 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_minishell *ms)
{
	size_t	nlen;
	char	*sv;

	nlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	sv = ft_malloc(nlen, ms);
	if (sv == NULL)
		return (NULL);
	if (s1 && s2)
	{
		ft_strlcpy(sv, s1, ft_strlen(s1) + 1);
		ft_strlcat(sv, s2, nlen + 1);
	}
	else if (s1)
		ft_strlcpy(sv, s1, ft_strlen(s1) + 1);
	else if (s2)
		ft_strlcpy(sv, s2, ft_strlen(s2) + 1);
	else
		*sv = 0;
	return (sv);
}
