/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:41:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/27 14:39:28 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_var(char *s, t_minishell *ms)
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

char	*replace_var(char *s, size_t x, t_minishell *ms)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	*ret_v;

	if (!s || s[x] == 0)
		return (s);
	tmp2 = read_var(&s[x + 1], ms);
	if (!tmp2 | !tmp2[0])
		printf("$%c : not a valid identifier\n", s[x + 1]);
	tmp = get_env_value(tmp2, ms);
	ft_free(tmp2, ms);
	if (!tmp)
		tmp = (ft_strdup("", ms));
	tmp2 = ft_substr(s, 0, x, ms);
	ret_v = ft_strjoin(tmp2, tmp, ms);
	ft_free(tmp2, ms);
	ft_free(tmp, ms);
	i = x + 1;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	if (!ft_isalpha(s[x + 1]) && s[x + 1] != '_')
		i = x + 2;
	// printf("s[i] = %s |\n", &s[i]);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	ft_free(tmp, ms);
	return (ret_v);
}
