/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:22:05 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/18 17:28:16 by ccambium         ###   ########.fr       */
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
	if (!tab || !tab[0])
		return (ft_strdup("", ms));
	ret_v = ft_strjoin("", tab[0], ms);
	if (!ret_v)
		return (NULL);
	while (tab[++i] != NULL)
	{
		tmp = ft_strjoin(ret_v, tab[i], ms);
		if (!tmp)
			return (ret_v);
		ft_free(ret_v, ms);
		ret_v = tmp;
	}
	return (ret_v);
}

static char	get_char_target(char *s)
{
	char	ret_v;

	ret_v = 0;
	if (ft_strchr(s, '"') && ft_strchr(s, '\''))
		ret_v = char_ternary(
				ft_strchr(s, '"') < ft_strchr(s, '\''), '"', '\'');
	else if (ft_strchr(s, '"'))
		ret_v = '"';
	else if (ft_strchr(s, '\''))
		ret_v = '\'';
	return (ret_v);
}

static int	count_quotes(char *s)
{
	int		ret_v;
	size_t	i;

	ret_v = 0;
	i = -1;
	while (*(s + ++i))
		if (*(s + i) == '\'' || *(s + i) == '"')
			ret_v ++;
	if (ret_v % 2 != 0)
		return (++ret_v / 2);
	return (ret_v / 2);
}

static char	*remove_quotes(char *s, t_minishell *ms, int depth)
{
	char	to_find;
	char	**tmp;
	char	*ret_v;
	int		ndepth;
	size_t	x;

	if (depth == 1)
		return (s);
	tmp = ft_malloc(sizeof(char *) * 4, ms);
	if (!tmp || !s || (!ft_strchr(s, '"') && !ft_strchr(s, '\'')))
		return (s);
	to_find = get_char_target(s);
	x = size_t_ternary(ft_strchr(s, to_find) - s > 0,
			ft_strchr(s, to_find) - s, 0);
	tmp[0] = ft_substr(s, 0, x, ms);
	tmp[1] = ft_substr(s, x + 1, (ft_strchr(&s[x + 1], to_find) - s) - x - 1, ms);
	ndepth = count_quotes(tmp[1]);
	if (ndepth > 1)
		tmp[1] = remove_quotes(tmp[1], ms, ndepth);
	tmp[2] = ft_substr(s, ft_strchr(&s[x + 1], to_find) - s + 1, ft_strlen(s), ms);
	ndepth = count_quotes(tmp[2]);
	if (ndepth)
		tmp[2] = remove_quotes(tmp[2], ms, 0);
	tmp[3] = NULL;
	ret_v = ft_concate(tmp, ms);
	if (!tmp[0] || !tmp[1] || !tmp[2] || !ret_v)
		return (s);
	free_split(tmp, ms);
	ft_free(s, ms);
	return (ret_v);
}

void	delete_quotes(t_token *token, t_minishell *ms)
{
	t_arg	*arg;

	if (!token->cmd)
		return ;
	token->cmd = remove_quotes(token->cmd, ms, 0);
	if (!token->cmd)
		return ;
	arg = token->arg_head;
	while (arg)
	{
		arg->value = remove_quotes(arg->value, ms, 0);
		if (!arg->value)
			return ;
		arg = arg->next;
	}
}
