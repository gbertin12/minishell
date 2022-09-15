/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:58:34 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/15 08:59:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	did_print(t_file *file, t_file *head)
{
	t_file	*f;

	f = head;
	while (f && f != file)
	{
		if (!ft_strncmp(f->path, file->path, ft_strlen(f->path)))
			return (1);
		f = f->next;
	}
	return (0);
}

void	put_error_fd(t_file *file, t_file *head, t_minishell *ms)
{
	t_file_error	*new_err;

	if (did_print(file, head))
		return ;
	if (ms->err_head == NULL)
	{
		new_err = ft_malloc(sizeof(t_file_error), ms);
		ms->err_head = new_err;
	}
	else
	{
		new_err = ft_malloc(sizeof(t_file_error), ms);
		add_end_err(ms->err_head, new_err);
	}
	new_err->next = NULL;
	new_err->err = ft_strjoin("minishell: ", file->path, ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, ": ", ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, strerror(errno), ms);
	if (!new_err->err)
		return ;
	new_err->err = ft_strjoin(new_err->err, "\n", ms);
}
