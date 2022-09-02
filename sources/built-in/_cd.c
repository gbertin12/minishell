/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:47:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 13:22:11 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_err(int err, char *msg_err)
{
	if (errno == err)
		perror(msg_err);
}

static char	replace_pwd_in_env(char *value_oldpwd, char *n_path,
								t_minishell *ms)
{
	char	*value_pwd;

	value_pwd = get_pwd(ms);
	if (n_path)
		value_pwd = n_path;
	modify_env("OLDPWD", value_oldpwd, ms);
	modify_env("PWD", value_pwd, ms);
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
		n_path = check_cd_path(path, all_cdpath, ms);
		if (n_path)
			replace_pwd_in_env(value_oldpwd, n_path, ms);
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
