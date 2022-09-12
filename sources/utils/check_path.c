/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:59:00 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/12 10:01:55 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_cd_path(char *path, char **all_cdpath, t_minishell *ms)
{
	char	*n_path;

	while (*all_cdpath)
	{
		n_path = ft_strjoin(*all_cdpath, "/", ms);
		if (!n_path)
			return (NULL);
		n_path = ft_strjoin(n_path, path, ms);
		if (!n_path)
			return (NULL);
		if (access(n_path, 0) != -1)
		{
			if (chdir(n_path) == -1)
				return (NULL);
			printf("%s\n", n_path);
			return (n_path);
		}
		ft_free(n_path, ms);
		all_cdpath++;
	}
	return (NULL);
}
