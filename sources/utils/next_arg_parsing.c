/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_arg_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:59:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 14:35:12 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	in_quotes(char	*cmd, long long i)
{
	char		quote;

	quote = cmd[i];
	if (ft_strchr(&cmd[++i], quote))
	{
		while (cmd[i] != quote)
			i++;
	}
	else
	{
		if (quote == '\'')
			ft_putstr_fd("Error parsing : \' not close\n", 0);
		else
			ft_putstr_fd("Error parsing : \" not close\n", 0);
		return (-1);
	}
	return (i);
}

long long	get_size_of_cmd(char *cmd)
{
	long long	i;

	i = 0;
	while (cmd[i] && !is_space(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = in_quotes(cmd, i);
		if (i == -1)
			return (i);
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (i);
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
