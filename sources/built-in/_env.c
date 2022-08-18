/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:52:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 03:50:28 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_env(t_minishell *ms)
{
	char	**s;
	int		i;
	char	*tmp;

	s = env_to_tab(ms);
	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		tmp = ft_strjoin(s[i], "\n", ms);
		ft_putstr_fd(tmp, 1);
		ft_free(tmp, ms);
	}
	i = -1;
	while (s[++i])
		ft_free(s[i], ms);
	return (1);
}
