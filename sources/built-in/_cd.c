/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:56:23 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 09:40:20 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_pwd(t_minishell *ms)
{
	char	v_print[50];
	char	*v_ret;

	v_ret = NULL;
	if (getcwd(v_print, 50) == NULL)
	{
		if (errno == ERANGE)
			perror("ERANGE");
		else if (errno == EFAULT)
			perror("EFAULT");
		else if (errno == EIO)
			perror("EIO");
		else if (errno == EACCES)
			perror("EACCES");
		return (NULL);
	}
	v_ret = ft_strdup(v_print, ms);
	return (v_ret);
}

void	check_err(int err, char *msg_err)
{
	if (errno == err)
		perror(msg_err);
}

static char	replace_pwd_in_env(char *value_oldpwd, t_minishell *ms)
{
	char	*key_pwd;
	char	*key_oldpwd;
	char	*value_pwd;

	key_pwd = NULL;
	key_oldpwd = NULL;
	value_pwd = NULL;
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
	return (1);
}

static char	exec_chdir(char *path, t_minishell *ms)
{
	char	*value_oldpwd;

	value_oldpwd = get_pwd(ms);
	if (chdir(path) == -1)
	{
		strerror(errno);
		return (1);
	}
	replace_pwd_in_env(value_oldpwd, ms);
	return (0);
}

char	_cd(t_token *token, t_minishell *ms)
{
	size_t	nb_arg;

	nb_arg = count_arg(token->arg_head);
	if (nb_arg > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (0);
	}
	if (nb_arg == 0)
		return (exec_chdir("/home", ms));
	return (exec_chdir(token->arg_head->value, ms));
}
