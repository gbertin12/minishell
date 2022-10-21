/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:47:11 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 10:00:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_err(char *path, t_minishell *ms)
{
	char	*err;

	err = NULL;
	err = ft_strjoin(err, "minishell: cd: ", ms);
	if (!err)
		return (1);
	err = ft_strjoin(err, path, ms);
	if (!err)
		return (1);
	err = ft_strjoin(err, ": ", ms);
	if (!err)
		return (1);
	if (errno == 116)
	{
		err = ft_strjoin(err, "No such file or directory\n", ms);
		if (!err)
			return (1);
	}
	else
	{
		err = ft_strjoin(err, strerror(errno), ms);
		if (!err)
			return (1);
		err = ft_strjoin(err, "\n", ms);
		if (!err)
			return (1);
	}
	ft_putstr_fd(err, 2);
	return (1);
}

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

	value_pwd = get_pwd(ms);
	if (n_path)
		value_pwd = n_path;
	else
		value_pwd = get_pwd(ms);
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

static void	exec_child(t_token *token, t_minishell *ms)
{
	init_execute(token, ms);
	redir_out(token);
	if (_cd(token, ms))
		exit_child(1, ms);
	else
		exit_child(0, ms);
}

static int	exec_in_child(t_token *token, t_minishell *ms)
{
	int	ret_v;

	if (token->next)
	{
		if (pipe(token->pipefd))
			return (1);
	}
	token->pid = fork();
	if (token->pid == 0)
	{
		if (ms->exec->last)
		{
			close(ms->exec->last->pipefd[0]);
			close(ms->exec->last->pipefd[1]);
		}
		exec_child(token, ms);
		ret_v = g_lretv;
		exit_child(ret_v, ms);
	}
	return (1);
}

int	exec_cd(t_token *token, t_minishell *ms)
{
	if (count_token(ms->t_head) > 1)
		exec_in_child(token, ms);
	else
	{
		if (init_exec_no_child(token) == 130)
			return (130);
		if (init_exec_no_child(token) == -1)
			return (0);
		if (init_exec_no_child(token) == 1)
			return (1);
		if (_cd(token, ms))
			return (1);
		else
			return (0);
	}
	return (0);
}
