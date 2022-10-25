/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:37:12 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/25 15:37:35 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_var_multi(char *s, size_t x, char *value, t_minishell *ms)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	*ret_v;

	tmp2 = ft_substr(s, 0, x, ms);
	if (!tmp2)
		return (NULL);
	ret_v = ft_strjoin(tmp2, value, ms);
	ft_free(tmp2, ms);
	i = x + 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	i = size_t_ternary(!ft_isalpha(s[x + 1]) && s[x + 1] != '_', x + 2, i);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	if (!tmp)
		return (NULL);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	if (!ret_v)
		return (tmp);
	ft_free(tmp, ms);
	return (ret_v);
}
