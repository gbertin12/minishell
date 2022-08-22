/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_arg_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:59:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 10:59:18 by gbertin          ###   ########.fr       */
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

int	check_next_sep(char c, char *s)
{
	size_t	i;

	i = 0;
	while (is_space(s[i]))
	{
		if (s[i + 1] == '>')
			return (0);
		if (ft_isprint(s[i + 1]))
			i++;
	}

}

long long	next_arg(char *s, t_token *token, t_minishell *ms)
{
	long long	size;

	if (s[0] == '>')
		return (add_output(s, token, ms));
	else if (s[0] == '<')
		return (add_input(s, token, ms));
	if (token->cmd == NULL)
	{
		size = get_size_of_cmd(s);
		if (size < 0)
			return (-1);
		token->cmd = ft_substr(s, 0, size, ms);
	}
	else
		return (add_arg(s, token, ms));
	return (size);
}
