/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:41:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/21 16:02:35 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_var(char *s, size_t x, t_minishell *ms)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	*ret_v;

	if (!s || s[x] == 0)
		return (s);
	tmp2 = read_var(&s[x + 1], ms);
	tmp = get_env_value(tmp2, ms);
	ret_v = ft_strjoin(ft_substr(s, 0, x, ms), tmp, ms);
	ft_free(tmp2, ms);
	i = x + 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	i = size_t_ternary(!ft_isalpha(s[x + 1]) && s[x + 1] != '_', x + 2, i);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	if (!ret_v)
		return (NULL);
	ft_free(tmp, ms);
	return (ret_v);
}
