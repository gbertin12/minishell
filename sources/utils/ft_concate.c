/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:06:22 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 15:12:23 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_concate(char **tab, t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	size_t	i;

	i = 0;
	ret_v = NULL;
	if (!tab || !tab[0])
		return (ft_strdup("", ms));
	ret_v = ft_strjoin("", tab[0], ms);
	if (!ret_v)
		return (NULL);
	while (tab[++i] != NULL)
	{
		tmp = ft_strjoin(ret_v, tab[i], ms);
		if (!tmp)
			return (ret_v);
		ft_free(ret_v, ms);
		ret_v = tmp;
	}
	return (ret_v);
}
