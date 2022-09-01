/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:47:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/01 09:55:01 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_err(int err, char *msg_err)
{
	if (errno == err)
		perror(msg_err);
}

static char	replace_pwd_in_env(char *value_oldpwd, char *n_path, t_minishell *ms)
{
	char	*key_pwd;
	char	*key_oldpwd;
	char	*value_pwd;

	key_pwd = NULL;
	key_oldpwd = NULL;
	value_pwd = NULL;
	if (n_path)
		value_pwd = n_path;
	else
		value_pwd = get_pwd(ms);
	key_oldpwd = ft_strdup("OLDPWD", ms);
	if (!key_oldpwd)
		return (0);
	if (do_env_key_exist(key_oldpwd, ms))
		replace_env_value(key_oldpwd, value_oldpwd, ms);
	else
		add_env_key_value(key_oldpwd, value_oldpwd, ms);
	key_pwd = ft_strdup("PWD", ms);
	if (!key_pwd)
		return (0);
	if (do_env_key_exist(key_pwd, ms))
		replace_env_value(key_pwd, value_pwd, ms);
	else
		add_env_key_value(key_pwd, value_pwd, ms);
	return (0);
}

static char	exec_chdir(char *path, t_minishell *ms)
{
	char	*value_oldpwd;
	char	*n_path;
	char	**all_cdpath;

	value_oldpwd = get_pwd(ms);
	if (do_env_key_exist("CDPATH", ms) && (path[0] != '.' && path[1] != '.'))
	{
		all_cdpath = ft_split(get_env_value("CDPATH", ms), ':', ms);
		while (*all_cdpath)
		{
			n_path = ft_strjoin(*all_cdpath, "/", ms);
			n_path = ft_strjoin(n_path, path, ms);
			if (access(n_path, 0) != -1)
			{
				if (chdir(n_path) == -1)
				{
					perror("minishell ");
					return (1);
				}
				replace_pwd_in_env(value_oldpwd, n_path, ms);
				printf("%s\n", n_path);
				return (0);
			}
			ft_free(n_path, ms);
			all_cdpath++;
		}
	}
	if (access(path, 0) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (0);
	}
	if (chdir(path) == -1)
	{
		strerror(errno);
		return (0);
	}
	replace_pwd_in_env(value_oldpwd, NULL, ms);
	return (0);
}

char	_cd(t_token *token, t_minishell *ms)
{
	size_t	nb_arg;
	char	*home_path;

	home_path = get_env_value("HOME", ms);
	if (home_path == NULL)
		home_path = "/home";
	nb_arg = count_arg(token->arg_head);
	if (nb_arg == 0)
		return (exec_chdir(home_path, ms));
	return (exec_chdir(token->arg_head->value, ms));
}

int	exec_cd(t_token *token, t_minishell *ms)
{
	if (count_token(ms->t_head) == 1)
	{
		if (_cd(token, ms))
			return (0);
	}
	return (1);
}
