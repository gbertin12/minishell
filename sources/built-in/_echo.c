/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:16:24 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/25 17:36:59 by ccambium         ###   ########.fr       */
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
	char		flag;

	arg = token->arg_head;
	while (arg)
	{
		if (check_flag(arg->value))
			flag++;
		else
			break ;
		arg = arg->next;
	}
	while (arg)
	{
		printf("%s", arg->value);
		arg = arg->next;
	}
	if (!flag)
		printf("\n");
	return (0);
}
