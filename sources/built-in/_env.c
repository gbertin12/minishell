/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:52:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/16 15:09:53 by gbertin          ###   ########.fr       */
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
		tmp = ft_strjoin(s[i], "\n");
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
	i = -1;
	while (s[++i])
		free(s[i]);
	return (1);
}
