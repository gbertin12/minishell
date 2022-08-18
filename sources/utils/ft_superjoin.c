/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:35:41 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 03:49:42 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_superjoin(char **s, t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	size_t	i;

	i = 0;
	ret_v = NULL;
	if (!s[1])
		return (ft_strdup("", ms));
	while (s[++i] != NULL)
	{
		tmp = ft_strjoin("", s[i], ms);
		ft_free(s[i], ms);
		ft_free(ret_v, ms);
		ret_v = tmp;
		if (s[i + 1])
		{
			tmp = ft_strjoin(ret_v, "=", ms);
			ft_free(ret_v, ms);
			ret_v = tmp;
		}
	}
	return (ret_v);
}
