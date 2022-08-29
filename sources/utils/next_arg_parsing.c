/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_arg_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:59:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 14:00:04 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	get_size_of_cmd(char *cmd)
{
	long long	i;
	char		quote;

	i = 0;
	while (cmd[i] && !is_space(cmd[i]))
	{
		if (cmd[i] == '|' || !ft_isalnum(cmd[i]))
			return (i);
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i];
			i++;
			if (ft_strchr(&cmd[i], quote))
			{
				while (cmd[i] != quote)
					i++;
				i++;
				if (is_space(cmd[i]))
					return (i);
				if (cmd[i] == '\'' || cmd[i] == '\"')
					i--;
			}
			else
			{
				if (quote == '\'')
					ft_putstr_fd("Error parsing : \' not close\n", 0);
				else
					ft_putstr_fd("Error parsing : \" not close\n", 0);
				return (-1);
			}		
		}
		i++;
	}
	return (i);
}

long long	next_arg(char *s, t_token *token, t_minishell *ms)
{
	long long	size;
	size_t		i;

	if (s[0] == '>')
		return (add_output(s, token, ms));
	else if (s[0] == '<')
		return (add_input(s, token, ms));
	if (token->cmd == NULL)
	{
		i = 0;
		while (is_space(s[i]))
			i++;
		size = get_size_of_cmd(&s[i]);
		if (size < 0)
			return (-1);
		token->cmd = ft_substr(s, i, size, ms);
	}
	else
		return (add_arg(s, token, ms));
	return (size + i);
}
