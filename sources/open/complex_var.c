/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:12:36 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/19 09:34:42 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_size_key(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '$' || path[i] == '\'' || path[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

static int	get_size_var(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '$' || path[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

char	*complexe_var(char *path, t_minishell *ms)
{
	int		i;
	char	*ret_v;
	size_t	size;
	char	*tmp;

	i = 0;
	ret_v = "";
	while (path[i] != '\0' && path[i] != '\"')
	{
		size = get_size_var(&path[i]);
		i += size;
		if (path[i] == '$')
			ret_v = ft_strjoin(ret_v, get_value_key(&path[i], ms), ms);
		else
		{
			tmp = ft_malloc(sizeof(char) * size + 1, ms);
			if (!tmp)
				return (NULL);
			ft_strlcpy(tmp, &path[i - size], size);
			ret_v = ft_strjoin(ret_v, tmp, ms);
		}	
		if (!ret_v)
			return (NULL);
	}
	return (ret_v);
}
