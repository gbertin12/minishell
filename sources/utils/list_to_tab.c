/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:40 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/13 13:00:55 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab(t_minishell *ms)
{
	char	**ret_v;
	char	*s_tmp;
	size_t	i;
	t_env	*tmp;

	ret_v = ft_malloc(sizeof(char *) * (count_env(ms->e_head) + 1), ms);
	if (!ret_v)
		return (ret_v);
	i = 0;
	tmp = ms->e_head;
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
