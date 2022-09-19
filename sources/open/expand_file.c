/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:11:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/19 09:17:43 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pos_next_var(char *path)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	if (path[i] == '\"')
	{
		while (path[i] != '\"')
			i++;
		return (i + 1);
	}
	if (path[i] == '$')
	{
		return (get_size_key(&path[i + 1]) + 1);
	}
	while (path[i])
	{
		if (path[i] == '\'')
			flag = char_ternary(flag, 0, 1);
		if ((path[i] == '\"' || path[i] == '$') && flag == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*get_value_key(char *path, t_minishell *ms)
{
	int		i;
	size_t	size;
	char	*key;
	char	*ret_v;

	i = 1;
	size = get_size_key(&path[i]) + 1;
	key = ft_malloc(sizeof(char) * size + 1, ms);
	if (!key)
		return (NULL);
	if (path[i] == '\0')
		return ("$");
	ft_strlcpy(key, &path[i], size);
	key[size] = '\0';
	ret_v = replace_value_file(key, ms);
	if (!ret_v)
		return (NULL);
	ft_free(key, ms);
	return (ret_v);
}

static char	*get_next_var(char *path, t_minishell *ms)
{
	int		i;
	char	*ret_v;

	i = 0;
	ret_v = NULL;
	if (path[i] != '$' && path[i] != '\"' && path[i])
		ret_v = simple_var(path);
	else if (path[i] == '$')
		ret_v = get_value_key(&path[i], ms);
	else
		ret_v = complexe_var(path, ms);
	return (ret_v);
}

static int	is_ambiguous(char *value, t_minishell *ms)
{
	if (ft_split_set(value, " \n\r\v\t\f", ms)[1])
		return (1);
	return (0);
}

char	*expand_file(char *path, t_minishell *ms)
{
	char	*new_path;
	char	*save;
	char	*tmp;
	int		i;
	int		ambiguous;

	i = 0;
	ambiguous = 0;
	new_path = "";
	save = ft_strdup(path, ms);
	while (path[i])
	{
		tmp = get_next_var(&path[i], ms);
		if (path[i] == '$' && ambiguous != 1 && tmp && tmp[0] != '\0')
			ambiguous = is_ambiguous(tmp, ms);
		new_path = ft_strjoin(new_path, tmp, ms);
		if (!new_path)
			break ;
		i += pos_next_var(&path[i]);
	}
	if (!check_ambiguous(new_path, save, ambiguous))
		return (NULL);
	return (new_path);
}
