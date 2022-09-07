/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:43 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/07 12:09:23 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	check_input2(char *s, size_t i, char *flag)
{
	if (!between_quote(s, i)
		&& (s[i] == '<' || s[i] == '>' || s[i] == '|')
		&& !*flag)
	{
		*flag = 1;
		if (s[i] == '|')
			*flag = 2;
		if ((s[i + 1] == '<' || s[i + 1] == '>') && *flag == 1)
			i++;
	}
	else if (!between_quote(s, i)
		&& (s[i] == '<' || s[i] == '>' || s[i] == '|')
		&& *flag)
	{
		if (*flag != 2 && s[i] != '|')
		{
			printf("minishell : syntax error near unexpected token `%c'\n",
				s[i]);
			return (1);
		}
	}
	else if ((s[i] == '"' || s[i] == '\'' || ft_isalnum(s[i])) && *flag)
		*flag = 0;
	return (0);
}

char	check_input(char *s)
{
	size_t	i;
	char	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (check_input2(s, i, &flag))
			return (1);
		i++;
	}
	if (flag)
	{
		printf("minishell : syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
