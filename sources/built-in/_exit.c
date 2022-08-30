/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:14:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 12:34:14 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_int(int i, char *nbr, char *max)
{
	while (nbr[i] == '0' && nbr[i + 1] != 0)
	{
		if (ft_strlen(&nbr[i]) < 20)
			return (0);
		i++;
	}
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
	if (!ft_check_int(i, nbr, max))
	{
		ms->l_retv = 2;
		printf("bash: exit: %s: numeric argument required\n", nbr);
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
			printf("bash: exit: %s: numeric argument required\n",
				token->arg_head->value);
			return (1);
		}
	}
	if (count_arg(ms->t_head->arg_head) > 1)
	{
		ms->l_retv = 1;
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (check_max_int(token->arg_head->value, ms))
		return (1);
	return (0);
}

int	b_exit(t_token *token, t_minishell *ms)
{
	printf("exit\n");
	if (token->arg_head)
	{
		if (check_arg(token, ms))
			return (1);
		ms->l_retv = ft_atoll(token->arg_head->value) % 256;
	}
	return (0);
}