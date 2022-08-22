/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:06:39 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 11:12:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	add_arg(char *s, t_token *token, t_minishell *ms)
{
	t_arg		*n_arg;
	long long	size;

	if (!s || s[0] == '\0')
		return (0);
	size = get_size_of_cmd(s);
	if (size < 0)
		return (-1);
	n_arg = ft_malloc(sizeof(t_arg), ms);
	n_arg->value = ft_substr(s, 0, size, ms);
	n_arg->next = NULL;
	if (token->arg_head == NULL)
		token->arg_head = n_arg;
	else
		add_end_arg(token->arg_head, n_arg);
	return (size);
}

long long int	add_output(char *s, t_token *token, t_minishell *ms)
{
	long long int	ret_v;
	t_file			*file;
	long long int	size;

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
	size = get_size_of_cmd(&s[ret_v]);
	if (size < 0)
		return (-1);
	file->path = ft_substr(s, (size_t)ret_v, size, ms);
	file->type = 1;
	add_end_file(token, file);
	ret_v += size;
	return (ret_v);
}

long long int	add_input(char *s, t_token *token, t_minishell *ms)
{
	long long int	ret_v;
	t_file			*file;
	long long int	size;

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
	size = get_size_of_cmd(&s[ret_v]);
	file->path = ft_substr(s, (size_t)ret_v, size, ms);
	add_end_file(token, file);
	ret_v += size;
	return (ret_v);
}

long long int	add_input_before(char *s, t_token *token, t_minishell *ms)
{
	long long int	ret_v;
	t_file			*file;
	long long int	size;

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
	size = get_size_of_cmd(&s[ret_v]);
	file->path = ft_substr(s, (size_t)ret_v, size, ms);
	add_end_file(token, file);
	ret_v += size;
	return (ret_v);
}
