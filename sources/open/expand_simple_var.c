/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simple_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:17:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/17 10:36:54 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_size_simple(char *path)
{
	int		flag;
	size_t	i;
	size_t	size;

	flag = 0;
	i = 0;
	size = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '\'')
		{
			flag = char_ternary(flag, 0, 1);
		}
		if ((path[i] == '\"' || path[i] == '$') && flag == 0)
		{
			break ;
		}
		if (path[i] != '\'')
			size++;
		if (path[i] == '\'' && path[i + 1] == '\0')
			break ;
		i++;
	}
	printf("size = %zu\n", size);
	return (size);
}

char	*simple_var(char *path)
{
	char	*ret_v;
	size_t	size;
	size_t	index;
	size_t	i;

	index = 0;
	size = get_size_simple(path);
	ret_v = malloc(sizeof(char) * size + 1);
	if (!ret_v)
		return (NULL);
	i = 0;
	while (size > 0)
	{
		if (path[i] != '\'')
		{
			ret_v[index] = path[i];
			size--;
			index++;
		}
		i++;
	}
	ret_v[index] = '\0';
	return (ret_v);
}
