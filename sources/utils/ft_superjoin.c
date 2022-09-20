/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:35:41 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/20 17:49:04 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_superjoin(char *export, char **s, t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	size_t	i;

	i = 0;
	ret_v = NULL;
	if (!s[1] && (export && ft_strchr(export, '=')))
		return (ft_strdup("", ms));
	else if (!s[1])
		return (NULL);
	while (s[++i] != NULL)
	{
		tmp = ft_strjoin(string_ternary(ret_v != NULL, ret_v, ""), s[i], ms);
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
