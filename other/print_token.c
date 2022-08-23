/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:16:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/22 19:15:05 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

static	size_t	count_file(t_file *file_head)
{
	size_t		count;
	t_file		*tmp;

	count = 0;
	tmp = file_head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static	size_t	size_t_ternary(char condition, size_t a, size_t b)
{
	if (condition)
		return (a);
	return (b);
}

static size_t	largest_arg(t_arg *arg_hard)
{
	t_arg 	*tmp;
	size_t	largest;
	size_t	tmp_size;

	largest = 0;
	tmp = arg_hard;
	while (tmp)
	{
		tmp_size = ft_strlen(tmp->value);
		largest = size_t_ternary(tmp_size > largest, tmp_size, largest);
		tmp = tmp->next;
	}
	return (largest);
}

static size_t	largest_file(t_file *arg_hard)
{
	t_file *tmp;
	size_t	largest;
	size_t	tmp_size;

	largest = 0;
	tmp = arg_hard;
	while (tmp)
	{
		tmp_size = ft_strlen(tmp->path);
		largest = size_t_ternary(tmp_size > largest, tmp_size, largest);
		tmp = tmp->next;
	}
	return (largest);
}

void	print_token(t_token *token)
{
	size_t	x;
	size_t	y;
	size_t	nb_arg;
	size_t	nb_file;
	size_t	nb_lines;
	size_t	nb_cln_file;
	size_t	nb_cln_arg;
	size_t	nb_cln_cmd;
	size_t	nb_cln_max;

	x = 0;
	y = 0;
	nb_arg = count_arg(token->arg_head);
	nb_file = count_file(token->file_head);
	nb_lines = size_t_ternary(nb_arg > nb_file, nb_arg, nb_file);
	nb_cln_arg = largest_arg(token->arg_head);
	nb_cln_file = largest_file(token->file_head);
	nb_cln_cmd = ft_strlen(token->cmd);
	nb_cln_cmd = size_t_ternary(nb_cln_cmd > 5, nb_cln_cmd, 5);
	nb_cln_arg = size_t_ternary(nb_cln_arg > 6, nb_cln_arg, 6);
	nb_cln_file = size_t_ternary(nb_cln_file > 7, nb_cln_file, 7) + 4;
	nb_cln_max = nb_cln_cmd + nb_cln_arg + nb_cln_file + 10;
	while (x < nb_cln_max)
	{
		if (x == 0)
			printf("%c", '|');
		else if (x == nb_cln_max - 1)
			printf("%c", '|');
		else
			printf("%c", '-');
		x++;
	}
	x = 0;
	printf("%c", '\n');
	while (x < nb_cln_cmd)
	{
		if (x == 0 || x == nb_cln_cmd - 1)
			printf("%c", '|');
		else if (x == 1)
		{
			printf(" CMD ");
			x += 5;
			continue ;
		}
		else 
			printf(" ");
		x++;
	}
	x = 0;
	while (x < nb_cln_arg)
	{
		if (x == 0 || x == nb_cln_arg - 1)
			printf("%c", '|');
		else if (x == 1)
		{
			printf(" ARGS ");
			x += 6;
			continue ;
		}
		else 
			printf(" ");
		x++;
	}
	x = 0;
	while (x < nb_cln_file)
	{
		if (x == 0 || x == nb_cln_file - 1)
			printf("%c", '|');
		else if (x == 1)
		{
			printf(" FILES ");
			x += 7;
			continue ;
		}
		else 
			printf(" ");
		x++;
	}
}

int	main(void)
{
	t_token	token;
	t_file	file;
	t_file	file2;
	t_arg	arg;

	token.cmd = "testss";
	arg.value = "ahhhhhh";
	file.path = "/path/to/file";
	file2.path = "/path/to/file2";
	file.type = 0;
	file2.type = 1;
	file.next = &file2;
	file2.next = NULL;
	arg.next = NULL;
	token.arg_head = &arg;
	token.file_head = &file;
	print_token(&token);
}
