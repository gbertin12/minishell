/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:21:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/03 12:32:59 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	next_var(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && (between_quote(s, i) || s[i] != '$'))
		i++;
	return (i);
}

char	*heredoc_expand(char *s, t_minishell *ms)
{
	char	*tmp;
	size_t	i;

	if (s == NULL)
		return (s);
	i = next_var(s);
	while (s[i])
	{
		tmp = s;
		s = replace_var(s, i, ms);
		if (!s)
			s = tmp;
		else
		{
			ft_free(tmp, ms);
			ft_putstr_fd("free heredoc", 2);
		}
		i = next_var(s);
	}
	return (s);
}
