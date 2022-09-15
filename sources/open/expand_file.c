/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:11:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/15 09:41:41 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*fault_in_key(char *badkey, t_minishell *ms)
{
	char	*ret_v;
	int		i;

	i = 0;
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
	return (ret_v);
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
		return (fault_in_key(badkey, ms));
	return (ret_v);
}

static char	*good_key(char	*goodkey, t_minishell *ms)
{
	char	*ret_v;

	ret_v = get_env_value(goodkey, ms);
	return (ret_v);
}

static char	*replace_value_file(char **split, int flag, t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;

	ret_v = "";
	if (flag)
	{
		ret_v = ft_strjoin(ret_v, *split, ms);
		split++;
	}
	while (*split != NULL)
	{
		if (check_key_env(*split))
		{
			tmp = bad_key(*split, ms);
			if (tmp)
				ret_v = ft_strjoin(ret_v, bad_key(*split, ms), ms);
		}
		else
			ret_v = ft_strjoin(ret_v, good_key(*split, ms), ms);
		if (!ret_v)
			return (NULL);
		split++;
	}
	return (ret_v);
}

char	*expand_file(char *path, t_minishell *ms)
{
	int		i;
	int		flag;
	char	*tmp;
	char	*new_path;

	i = 0;
	tmp = ft_strdup(path, ms);
	if (!tmp)
		tmp = "";
	flag = 0;
	while (path[i])
	{
		
		i++;
	}
	if (!check_ambiguous(path, tmp, ms))
		return (NULL);
	return (path);
}
