/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_basic_environement.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:52:56 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/19 11:12:06 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_basic_environement(t_minishell *ms)
{
	t_env	*env;
	t_env	*e;

	modify_env("PWD", ms->pwd, ms);
	modify_env("SHLVL", "1", ms);
	env = ft_malloc(sizeof(t_env), ms);
	env->key = ft_strdup("PATH", ms);
	env->value = ft_strdup(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", ms);
	env->show = 1;
	env->next = NULL;
	e = ms->e_head;
	while (e->next)
		e = e->next;
	e->next = env;
}
