/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:31:02 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/15 21:10:33 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_superjoin(char **s)
{
	char	*ret_v;
	char	*tmp;
	size_t	i;

	i = 0;
	ret_v = NULL;
	while (s[++i] != NULL)
	{
		tmp = ft_strjoin("", s[i]);
		free(s[i]);
		free(ret_v);
		ret_v = tmp;
		if (s[i + 1])
		{
			tmp = ft_strjoin(ret_v, "=");
			free(ret_v);
			ret_v = tmp;
		}
	}
	return (ret_v);
}

void	copy_env(t_minishell *ms, char **env)
{
	size_t	i;
	char	**s;
	t_env	*e_tmp;
	t_env	*last;

	i = -1;
	last = NULL;
	if (env == NULL)
		return ;
	while (env[++i])
	{
		e_tmp = ft_malloc(sizeof(t_env), ms);
		if (!e_tmp)
			return ;
		if (ms->e_head == NULL)
			ms->e_head = e_tmp;
		s = ft_split(env[i], '=');
		e_tmp->key = s[0];
		e_tmp->value = ft_superjoin(s);
		free(s);
		if (last != NULL)
			last->next = e_tmp;
		e_tmp->next = NULL;
		last = e_tmp;
	}
}
