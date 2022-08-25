/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:16:24 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/25 16:01:11 by gbertin          ###   ########.fr       */
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
		printf("%s", arg->value);
		arg = arg->next;
	}
	if (!flag)
		printf("\n");
	close(fd);
	return (0);
}
