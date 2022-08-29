/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:42:16 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/28 13:04:27 by gbertin          ###   ########.fr       */
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

char	*make_path(t_exec *exec, t_minishell *ms)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	if (exec->path_absolute == NULL || ft_search_char(exec->token->cmd))
	{
		if (access(exec->token->cmd, 0) == 0)
			return (ft_strdup(exec->token->cmd, ms));
		return (NULL);
	}
	while (exec->path_absolute[i] != NULL)
	{
		tmp = ft_strjoin(exec->path_absolute[i], "/", ms);
		path = ft_strjoin(tmp, exec->token->cmd, ms);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
