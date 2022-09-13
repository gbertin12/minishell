/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:11:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/12 14:13:10 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_var(char *s, t_minishell *ms)
{
	size_t	i;
	char	*ret_v;

	i = 0;
	if (s[i] == '?')
		return (ft_strdup("?", ms));
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (ft_strdup("", ms));
	while (s[i] && !is_space(s[i]) && s[i] != '$')
		i++;
	ret_v = ft_substr(s, 0, i, ms);
	return (ret_v);
}
