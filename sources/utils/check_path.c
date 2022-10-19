/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:59:00 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 12:35:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_cdpath(char *path, char *all_cdpath, t_minishell *ms)
{
	char	*n_path;

	if (all_cdpath[ft_strlen(all_cdpath) - 1] != '/')
	{
		n_path = ft_strjoin(all_cdpath, "/", ms);
		if (!n_path)
			return (NULL);
	}
	else
	{
		n_path = ft_strdup(all_cdpath, ms);
		if (!n_path)
			return (NULL);
	}
	n_path = ft_strjoin(n_path, path, ms);
	if (!n_path)
		return (NULL);
	return (n_path);
}

char	*check_cd_path(char *path, char **all_cdpath, t_minishell *ms)
{
	char	*n_path;
	int		i;

	i = 0;
	while (all_cdpath[i])
	{
		n_path = make_cdpath(path, all_cdpath[i], ms);
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
		i++;
	}
	return (NULL);
}

int	check_path(t_exec *exec, t_minishell *ms)
{
	if (ft_strchr(exec->token->cmd, '/') || !do_env_key_exist("PATH", ms))
	{
		if (access(exec->token->cmd, 0) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->token->cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	if (!exec->path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->token->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}
