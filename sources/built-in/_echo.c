/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:16:24 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/20 22:18:57 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_flag(char	*s)
{
	size_t	i;

	if (!s || s[0] != '-' || !s[0])
		return (0);
	i = 0;
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

static int	check_files(t_token *token)
{
	t_file	*file;

	file = token->file_head;
	while (file)
	{
		if (!file->type)
		{
			file = file->next;
			continue ;
		}
		if (!access(file->path, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("file not found or permission denied\n", 2);
			return (1);
		}
		file = file->next;
	}
	return (0);
	
}

static int	open_output(t_token *token)
{
	t_file	*file;
	int		fd;

	file = token->file_head;
	fd = 1;
	while (file)
	{
		if (fd > 0 && fd != 1)
			close(fd);
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("file not found or permission denied\n", 2);
			return (1);
		}
		file = file->next;
	}
	return (fd);
}

int	_echo(t_token *token)
{
	t_arg		*arg;
	int			e;
	int			fd;
	char		flag;

	arg = token->arg_head;
	flag = check_flag(arg->value);
	e = check_files(token);
	if (e)
		return (e);
	if (flag)
		arg = arg->next;
	fd = open_output(token);
	if (fd < 0)
		return (fd);
	while (arg)
	{
		ft_putstr_fd(arg->value, fd);
		arg = arg->next;
	}
	if (!flag)
		ft_putstr_fd("\n", fd);
	close(fd);
	return (0);
}
