/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   between_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:56:22 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/22 11:04:53 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	between_quote(char *s, size_t x)
{
	char	d_quote;
	char	quote;
	size_t	i;

	quote = 0;
	d_quote = 0;
	i = 0;
	while (s && s[i] && i <= x)
	{
		if (s[i] == '"' && !quote)
			d_quote = char_ternary(d_quote, 0, 1);
		if (s[i] == '\'' && !d_quote)
			quote = char_ternary(quote, 0, 1);
		i++;
	}
	return (quote);
}
