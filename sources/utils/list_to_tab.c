/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:40 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/07 12:12:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab2(char **ret_v, t_env *tmp, t_minishell *ms)
{
	char	*s_tmp;
	size_t	i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value)
		{
			s_tmp = ft_strjoin(tmp->key, "=", ms);
			ret_v[i] = ft_strjoin(s_tmp, tmp->value, ms);
			ft_free(s_tmp, ms);
		}
		else
			ret_v[i] = ft_strdup(tmp->key, ms);
		tmp = tmp->next;
		i++;
	}
	ret_v[i] = NULL;
	return (ret_v);
}

char	**env_to_tab(t_minishell *ms)
{
	char	**ret_v;
	size_t	nb_element;
	t_env	*tmp;

	nb_element = count_env(ms->e_head);
	ret_v = ft_malloc(sizeof(char *) * (nb_element + 1), ms);
	if (!ret_v)
		return (ret_v);
	tmp = ms->e_head;
	return (env_to_tab2(ret_v, tmp, ms));
}

static char	**fill_tab(int nb_element, t_token *token, t_minishell *ms)
{
	char	**ret_v;
	t_arg	*arg;
	size_t	i;

	arg = token->arg_head;
	ret_v = ft_malloc(sizeof(char *) * (nb_element + 2), ms);
	if (!ret_v)
		return (ret_v);
	ret_v[0] = ft_strdup(token->cmd, ms);
	i = 1;
	while (arg != NULL)
	{
		ret_v[i] = arg->value;
		arg = arg->next;
		i++;
	}
	ret_v[i] = NULL;
	return (ret_v);
}

char	**args_to_tab(t_token *token, t_minishell *ms)
{
	size_t	nb_element;
	t_arg	*arg;

	nb_element = 0;
	arg = NULL;
	if (token->arg_head)
	{
		arg = token->arg_head;
		if (!arg)
			return (NULL);
		nb_element = count_arg(token->arg_head);
	}
	return (fill_tab(nb_element, token, ms));
}
