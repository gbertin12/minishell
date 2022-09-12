/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:22:05 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/12 10:00:45 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_concate(char **tab, t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	size_t	i;

	i = 0;
	ret_v = NULL;
	if (!tab[0])
		return (ft_strdup("", ms));
	ret_v = ft_strjoin("", tab[0], ms);
	if (!ret_v)
		return (NULL);
	while (tab[++i] != NULL)
	{
		tmp = ft_strjoin(ret_v, tab[i], ms);
		ft_free(ret_v, ms);
		ret_v = tmp;
	}
	return (ret_v);
}

static char	get_char_target(char *s)
{
	char	ret_v;

	ret_v = 0;
	if (strchr(s, '"') && strchr(s, '\''))
		ret_v = char_ternary(
				strchr(s, '"') < strchr(s, '\''), '"', '\'');
	else if (strchr(s, '"'))
		ret_v = '"';
	else if (strchr(s, '\''))
		ret_v = '\'';
	return (ret_v);
}

static char	*remove_quotes(char *s, t_minishell *ms)
{
	char	to_find;
	char	**tmp;
	char	*ret_v;
	size_t	x;

	tmp = ft_malloc(sizeof(char *) * 4, ms);
	if (!tmp)
		return (s);
	if (!s || (!strchr(s, '"') && !strchr(s, '\'')))
		return (s);
	to_find = get_char_target(s);
	if (!to_find)
		return (s);
	x = size_t_ternary(strchr(s, to_find) - s > 0, strchr(s, to_find) - s, 0);
	tmp[0] = ft_substr(s, 0, x, ms);
	tmp[1] = ft_substr(s, x + 1, (ft_strrchr(s, to_find) - s) - x - 1, ms);
	tmp[2] = ft_substr(s, ft_strrchr(s, to_find) - s + 1, ft_strlen(s), ms);
	tmp[3] = NULL;
	ret_v = ft_concate(tmp, ms);
	ft_free(tmp[0], ms);
	ft_free(tmp[1], ms);
	ft_free(tmp[2], ms);
	ft_free(tmp, ms);
	ft_free(s, ms);
	return (ret_v);
}

void	delete_quotes(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	t_file	*file;

	token->cmd = remove_quotes(token->cmd, ms);
	if (!token->cmd)
		return ;
	arg = token->arg_head;
	file = token->file_head;
	while (arg)
	{
		arg->value = remove_quotes(arg->value, ms);
		if (!arg->value)
			return ;
		arg = arg->next;
	}
	while (file)
	{
		file->path = remove_quotes(file->path, ms);
		if (!file->path)
			return ;
		file = file->next;
	}
}

