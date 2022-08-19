/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:17:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/19 09:52:28 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	next_var(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	return (i);
}

static char	*read_var(char *s, t_minishell *ms)
{
	size_t	i;
	char	*ret_v;

	i = 0;
	while (s[i] && !is_space(s[i]) && s[i] != '$')
		i++;
	ret_v = ft_substr(s, 0, i, ms);
	return (ret_v);
}

static char	*replace_var(char *s, size_t x, t_minishell *ms)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	*ret_v;

	if (!s || s[x] == 0)
		return (s);
	printf("s[x] == %c && x = %lu\n", s[x], x);
	tmp2 = read_var(&s[x + 1], ms);
	tmp = get_env_value(tmp2, ms);
	ft_free(tmp2, ms);
	if (!tmp)
		tmp = (ft_strdup("", ms));
	tmp2 = ft_substr(s, 0, x, ms);
	ret_v = ft_strjoin(tmp2, tmp, ms);
	ft_free(tmp2, ms);
	ft_free(tmp, ms);
	i = x + 1;
	while (s[i] && !is_space(s[i]) && s[i] != '$')
		i++;
	tmp = ft_substr(s, x + i, ft_strlen(&s[x + i]), ms);
	ret_v = ft_strjoin(ret_v, tmp, ms);
	ft_free(tmp, ms);
	return (ret_v);
}

static void	expand_arg(t_token *token, t_minishell *ms)
{
	t_arg	*arg;
	size_t	i;
	char	*tmp;

	arg = token->arg_head;
	while (arg)
	{
		if (arg->apos == 1)
		{
			arg = arg->next;
			continue ;
		}
		if (arg->value)
		{
			i = next_var(arg->value);
			while (arg->value[i])
			{
				if (arg->value[i] == 0)
					break ;
				tmp = arg->value;
				arg->value = replace_var(arg->value, i, ms);
				if (!arg->value)
					arg->value = tmp;
				else
					ft_free(tmp, ms);
				i = next_var(arg->value);
			}
		}
		arg = arg->next;
	}
}

static void	expand_file(t_token *token, t_minishell *ms)
{
	t_file	*file;
	size_t	i;
	char	*tmp;

	file = token->file_head;
	while (file)
	{
		if (file->apos == 1)
		{
			file = file->next;
			continue ;
		}
		if (file->path)
		{
			i = next_var(file->path);
			while (file->path[i])
			{
				if (file->path[i] == 0)
					break ;
				tmp = file->path;
				file->path = replace_var(file->path, i, ms);
				if (!file->path)
					file->path = tmp;
				else
					ft_free(tmp, ms);
				i = next_var(file->path);
			}
		}
		file = file->next;
	}
}

static void	expand_cmd(t_token *token, t_minishell *ms)
{
	char	*tmp;
	size_t	i;

	i = next_var(token->cmd);
	while (token->cmd[i])
	{
		if (token->cmd[i] == 0)
			return ;
		tmp = token->cmd;
		token->cmd = replace_var(token->cmd, i, ms);
		if (!token->cmd)
			token->cmd = tmp;
		else
			ft_free(tmp, ms);
		i = next_var(token->cmd);
	}
}

void	expand(t_minishell *ms)
{
	t_token	*token;

	token = ms->t_head;
	while (token)
	{
		expand_cmd(token, ms);
		expand_arg(token, ms);
		expand_file(token, ms);
		token = token->next;
	}
}
