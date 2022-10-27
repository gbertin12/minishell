/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:24:36 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/27 10:15:09 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_oldpwd_null(t_minishell *ms)
{
	t_env	*head;

	head = ms->e_head;
	while (head)
	{
		if (ft_strcmp(head->key, "OLDPWD"))
		{
			head->value = NULL;
			head->show = 1;
			return ;
		}
		head = head->next;
	}
}

static char	replace_pwd_in_env(char *value_oldpwd, char *n_path,
								t_minishell *ms)
{
	char	*value_pwd;

	value_pwd = NULL;
	value_pwd = get_pwd(ms);
	if (n_path)
		value_pwd = n_path;
	else
		value_pwd = get_pwd(ms);
	if (value_pwd == NULL)
	{
		perror("chdir: error retrieving current directory:\
 getcwd: cannot access parent directories");
		return (1);
	}
	if (do_env_key_exist("PWD", ms))
	{
		modify_env("PWD", value_pwd, ms);
		modify_env("OLDPWD", value_oldpwd, ms);
	}
	else
		set_oldpwd_null(ms);
	if (ms->pwd)
		ft_free(ms->pwd, ms);
	ms->pwd = ft_strdup(value_pwd, ms);
	return (0);
}

static char	exec_chdir(t_token *token, char *path, t_minishell *ms)
{
	char	*value_oldpwd;
	char	*n_path;
	char	**all_cdpath;

	value_oldpwd = get_pwd(ms);
	if (do_env_key_exist("CDPATH", ms) && (path[0] != '.'
			&& path[1] != '.' && path[0] != '/')
		&& count_arg(token->arg_head) > 0)
	{
		all_cdpath = ft_split(get_env_value("CDPATH", ms), ':', ms);
		n_path = check_cd_path(path, all_cdpath, ms);
		if (n_path)
			return (replace_pwd_in_env(value_oldpwd, n_path, ms));
	}
	if (access(path, 0) == -1)
		return (check_err(path, ms));
	if (chdir(path) == -1)
		return (check_err(path, ms));
	replace_pwd_in_env(value_oldpwd, NULL, ms);
	return (0);
}

char	_cd(t_token *token, t_minishell *ms)
{
	size_t	nb_arg;
	char	*home_path;

	if (count_arg(token->arg_head) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	home_path = get_env_value("HOME", ms);
	nb_arg = count_arg(token->arg_head);
	if (nb_arg == 0 && (home_path && home_path[0]))
		return (exec_chdir(token, home_path, ms));
	else if (nb_arg == 0 && !do_env_key_exist("HOME", ms))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	else if (nb_arg == 0 && (!home_path || !home_path[0]))
		return (0);
	return (exec_chdir(token, token->arg_head->value, ms));
}
