/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:43 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/09 08:51:28 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	check_input2(char *s, size_t *i, char *flag)
// {
// 	if (!between_quote(s, *i)
// 		&& (s[*i] == '<' || s[*i] == '>' || s[*i] == '|')
// 		&& !*flag)
// 	{
// 		*flag = 1;
// 		if (s[*i] == '|')
// 			*flag = 2;
// 		if ((s[*i + 1] == '<' || s[*i + 1] == '>') && *flag == 1)
// 			*i += 1;
// 	}
// 	else if (!between_quote(s, i)
// 		&& (s[*i] == '<' || s[*i] == '>' || s[*i] == '|')
// 		&& *flag)
// 	{
// 		if (*flag != 2 && s[*i] != '|')
// 		{
// 			printf("minishell : syntax error near unexpected token `%c'\n",
// 				s[*i]);
// 			return (1);
// 		}
// 	}
// 	else if ((s[*i] == '"' || s[*i] == '\'' || ft_isalnum(s[*i])) && *flag)
// 		*flag = 0;
// 	return (0);
// }

// char	check_input(char *s)
// {
// 	size_t	i;
// 	char	flag;

// 	i = 0;
// 	flag = 0;
// 	while (s[i])
// 	{
// 		if (check_input2(s, &i, &flag))
// 			return (1);
// 		i++;
// 	}
// 	if (flag)
// 	{
// 		printf("minishell : syntax error near unexpected token `newline'\n");
// 		return (1);
// 	}
// 	return (0);
// }

static void	create_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\n', 2);
}

static void	error_file(t_file *f)
{
	if (f->next->type)
	{
		if (f->next->append)
			create_error("syntax error near unexpected token `>>'");
		else
			create_error("syntax error near unexpected token `>'");
	}
	else
	{
		if (f->next->append)
			create_error("syntax error near unexpected token `<<'");
		else
			create_error("syntax error near unexpected token `<'");
	}
}

static char	check_file(t_file *head)
{
	t_file	*f;

	f = head;
	while (f)
	{
		if (!f->path || !*f->path)
		{
			if (f->next)
				error_file(f);
			else
				create_error("syntax error near unexpected token `|'");
			return (1);
		}
		f = f->next;
	}
	return (0);
}

static char	check_token(t_token *t, t_token *head)
{
	if (token_is_empty(t))
	{
		if (count_token(head) == 1)
			return (1);
		if (t->next)
			create_error("syntax error near unexpected token `|'");
		else
			create_error("syntax error near unexpected token `newline'");
		return (1);
	}
	if (check_file(t->file_head))
		return (1);
	return (0);
}

char	check_input(t_token *head)
{
	t_token	*t;

	t = head;
	while (t)
	{
		if (check_token(t, head))
			return (1);
		t = t->next;
	}
	return (0);
}
