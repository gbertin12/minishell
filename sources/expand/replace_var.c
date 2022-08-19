/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:41:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/19 14:52:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_var(char *s, t_minishell *ms)
{
	size_t	i;
	char	*ret_v;

	i = 0;
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
	tmp = get_env_value(tmp2, ms);
	ft_free(tmp2, ms);
	if (!tmp)
		tmp = (ft_strdup("", ms));
	tmp2 = ft_substr(s, 0, x, ms);
	ret_v = ft_strjoin(tmp2, tmp, ms);
	ft_free(tmp2, ms);
	ft_free(tmp, ms);
	i = x + 1;
	while (s[i] && !is_space(s[i]) && s[i] != '$')
		i++;
	printf("s[i] = %s |\n", &s[i]);
	tmp = ft_substr(s, i, ft_strlen(&s[i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	ft_free(tmp, ms);
	return (ret_v);
}
