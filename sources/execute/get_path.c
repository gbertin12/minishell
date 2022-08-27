/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:42:16 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/27 16:01:27 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path_env(t_minishell *ms)
{
	char	**all_path;
	char	**env;
	size_t	i;

	i = 0;
	env = env_to_tab(ms);
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			while (*env[i] != '/' && *env[i] != '\0')
				env[i]++;
			all_path = ft_split(env[i], ':', ms);
			if (!all_path)
				return (NULL);
			return (all_path);
		}
		i++;
	}
	return (NULL);
}

int	ft_search_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*make_path(t_token *token, t_minishell *ms)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	if (ms->path_absolute == NULL || ft_search_char(token->cmd))
	{
		if (access(token->cmd, 0) == 0)
			return (ft_strdup(token->cmd, ms));
		return (NULL);
	}
	while (ms->path_absolute[i] != NULL)
	{
		tmp = ft_strjoin(ms->path_absolute[i], "/", ms);
		path = ft_strjoin(tmp, token->cmd, ms);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
