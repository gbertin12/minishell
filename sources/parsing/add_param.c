/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:06:39 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/19 12:58:03 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_arg(char *s, t_token *token, t_minishell *ms)
{
	t_arg	*n_arg;
	size_t	size;

	if (!s || s[0] == '\0')
		return ;
	size = search_next_sep(s);
	n_arg = ft_malloc(sizeof(t_arg), ms);
	n_arg->value = ft_substr(s, 0, size, ms);
	n_arg->next = NULL;
	if (token->arg_head == NULL)
		token->arg_head = n_arg;
	else
		add_end_arg(token->arg_head, n_arg);
}

long long int	add_output(char *s, t_token *token, t_minishell *ms)
{
	long long int	ret_v;
	t_file			*file;

	ret_v = 1;
	file = ft_malloc(sizeof(t_file), ms);
	ft_memset(file, 0, sizeof(t_file));
	if (s[ret_v] == '>')
	{
		ret_v++;
		file->append = 1;
	}
	if (!ft_isprint(s[ret_v]) && !is_space(s[ret_v]))
		return (-1);
	while (is_space(s[ret_v]))
		ret_v++;
	file->path = ft_substr(s, (size_t)ret_v, search_next_sep(&s[ret_v]), ms);
	file->type = 1;
	add_end_file(token, file);
	return (ret_v);
}

long long int	add_input(char *s, t_token *token, t_minishell *ms)
{
	long long int	ret_v;
	t_file			*file;

	ret_v = 1;
	file = ft_malloc(sizeof(t_file), ms);
	ft_memset(file, 0, sizeof(t_file));
	if (s[ret_v] == '<')
	{
		ret_v++;
		file->append = 1;
	}
	if (!ft_isprint(s[ret_v]) && !is_space(s[ret_v]))
		return (-1);
	while (is_space(s[ret_v]))
		ret_v++;
	file->path = ft_substr(s, (size_t)ret_v, search_next_sep(&s[ret_v]), ms);
	add_end_file(token, file);
	return (ret_v);
}

void	add_arg_w_quote(char *cmd, char quote, t_token *token, t_minishell *ms)
{
	t_arg	*n_arg;

	if (!cmd || cmd[0] == '\0')
		return ;
	n_arg = ft_malloc(sizeof(t_arg), ms);
	n_arg->value = cmd;
	n_arg->next = NULL;
	if (quote == '\'')
		n_arg->apos = 1;
	if (token->arg_head == NULL)
		token->arg_head = n_arg;
	else
		add_end_arg(token->arg_head, n_arg);
}
