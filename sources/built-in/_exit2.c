/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:25:41 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/10 11:52:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err_exit(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
}

int	no_valid_arg(t_arg *arg)
{
	t_arg	*begin;

	begin = arg;
	if (!begin)
		return (1);
	while (begin)
	{
		if (ft_strlen(begin->value) > 0)
			return (0);
		begin = begin->next;
	}
	return (1);
}

static int	ft_check_int(int i, char *nbr, char *max)
{
	if (ft_strlen(&nbr[i]) > 20)
		return (1);
	while (nbr[i] && *max)
	{
		if (*max < nbr[i])
			return (1);
		else if (*max > nbr[i])
			return (0);
		max++;
		i++;
	}
	return (0);
}

static int	check_max_int(char *nbr, t_minishell *ms)
{
	char	*max;
	int		i;

	i = 0;
	max = "9223372036854775807";
	if (ft_strlen(nbr) < 20)
		return (0);
	if (ft_strlen(nbr) < 21 && nbr[0] == '-')
		return (0);
	if (nbr[0] == '-')
	{
		max = "9223372036854775808";
		i++;
	}
	if (ft_check_int(i, nbr, max))
	{
		ms->l_retv = 2;
		print_err_exit(nbr, ": numeric argument required\n");
		return (1);
	}
	return (0);
}

int	check_arg(t_token *token, t_minishell *ms)
{
	int	i;

	i = -1;
	if (token->arg_head->value[0] == '-')
		i++;
	while (token->arg_head->value[++i])
	{
		if (!ft_isdigit(token->arg_head->value[i]))
		{
			ms->l_retv = 2;
			print_err_exit(token->arg_head->value,
				": numeric argument required\n");
			return (1);
		}
	}
	if (check_max_int(token->arg_head->value, ms))
		return (1);
	return (0);
}
