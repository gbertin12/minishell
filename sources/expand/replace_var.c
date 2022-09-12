/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:41:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/12 14:48:54 by ccambium         ###   ########.fr       */
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
	if (!tmp2 || !tmp2[0])
		printf("$%c : not a valid identifier\n", s[x + 1]);
	tmp = get_env_value(tmp2, ms);
	ft_free(tmp2, ms);
	tmp = string_ternary(tmp == NULL, ft_strdup("", ms), tmp);
	tmp2 = ft_substr(s, 0, x, ms);
	ret_v = ft_strjoin(tmp2, tmp, ms);
	ft_free(tmp2, ms);
	ft_free(tmp, ms);
	i = x + 1;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	i = size_t_ternary(!ft_isalpha(s[x + 1]) && s[x + 1] != '_', x + 2, i);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	ft_free(tmp, ms);
	return (ret_v);
}
