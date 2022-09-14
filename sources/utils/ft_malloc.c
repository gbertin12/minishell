/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:43:45 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/14 10:06:00 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_malloc(size_t size, t_minishell *ms)
{
	void	*ptr;
	t_obj	*obj;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	obj = malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_bzero(ptr, size);
	obj->ptr = ptr;
	obj->next = NULL;
	if (ms->o_head != NULL)
		add_end_obj(ms->o_head, obj);
	else
		ms->o_head = obj;
	return (ptr);
}

void	free_all(t_minishell *ms)
{
	t_obj	*x;
	t_obj	*next;

	x = ms->o_head;
	while (x != NULL)
	{
		free(x->ptr);
		next = x->next;
		free(x);
		x = next;
	}
}

void	ft_free(void *ptr, t_minishell *ms)
{
	t_obj	*x;
	t_obj	*last;

	last = NULL;
	x = ms->o_head;
	while (x != NULL)
	{
		if (&x->ptr == &ptr)
		{
			free(ptr);
			break ;
		}
		last = x;
		x = x->next;
	}
	if (x == NULL)
		return ;
	last->next = x->next;
	free(x);
}
