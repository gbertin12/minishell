/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:11:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/13 15:41:41 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ambiguous(char *path, char *print, t_minishell *ms)
{
	char	**split;

	if (path)
	{
		split = ft_split_set(path,  " \n\r\v\t\f", ms);
		if (!split)
			return (1);
	}
	if (!path || split[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}

static char	*bad_key(char *badkey, t_minishell *ms)
{
	char	*ret_v;
	int		i;

	i = 0;
	ret_v = NULL;
	if (!ft_isalpha(badkey[i]) && badkey[i] != '_')
	{
		if (!badkey[i + 1])
			return (NULL);
		ret_v = ft_malloc(sizeof(char) * ft_strlen(badkey) - i + 1, ms);
		if (ret_v)
			ft_strlcpy(ret_v, &badkey[1], ft_strlen(badkey));
		if (!ret_v)
			return (NULL);
	}
	else
	{
		while (badkey[i] != '\0')
		{
			if (!ft_isalnum(badkey[i]) && badkey[i] != '_')
			{
				ret_v = ft_malloc(sizeof(char) * ft_strlen(badkey) - i + 1, ms);
				if (ret_v)
					ft_strlcpy(ret_v, &badkey[i], ft_strlen(badkey) - i + 1);
				if (!ret_v)
					return (NULL);
			}
			i++;
		}
	}
	printf("ret v = %s\n", ret_v);
	return (ret_v);	
}

static char	*good_key(char	*goodkey, t_minishell *ms)
{
	char *ret_v;
	
	ret_v = get_env_value(goodkey, ms);
	return (ret_v);
}

static char	*replace_value_file(char **split, int flag, t_minishell *ms)
{
	char	*ret_v;
	int		i;

	i = 0;
	ret_v = "";
	if (flag)
	{
		ret_v = ft_strjoin(ret_v, split[0], ms);
		i++;
	}
	while (split[i] != NULL)
	{
		if (check_key_env(split[i]))
			ret_v = ft_strjoin(ret_v, bad_key(split[i], ms), ms);
		else
			ret_v = ft_strjoin(ret_v, good_key(split[i], ms), ms);
		if (!ret_v)
			return (NULL);
		i++;
	}
	return (ret_v);
}

char	*expand_file(char *path, t_minishell *ms)
{
	int		flag;
	char	**split;
	char	*tmp;

	tmp = ft_strdup(path, ms);
	flag = 0;
	if (path[0] != '$')
		flag = 1;
	split = ft_split(path, '$', ms);
	if (!split)
		return (NULL);
	path = replace_value_file(split, flag, ms);
	if (!check_ambiguous(path, tmp, ms))
		return (NULL);
	return (path);
}
