/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:17 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/26 14:57:51 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/prompt.h"

char	*get_prompt(t_minishell *ms, int x)
{
	char	*ret_v;
	char	*tmp;
	char	*pwd;
	char	*user;

	pwd = NULL;
	user = ft_strdup("minishell", ms);
	pwd = getcwd(NULL, 0);
	ret_v = ft_strjoin(RED, "┌──", ms);
	tmp = ft_strjoin(ret_v, YELLOW, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, "(", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, GREEN, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, user, ms);
	ft_free(user, ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, YELLOW, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, ")", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, RED, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, "──", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, YELLOW, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, "[", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, GREEN, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, pwd, ms);
	free(pwd);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, YELLOW, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, "]", ms);
	ft_free(tmp, ms);
	if (x == 1)
		return (ret_v);
	tmp = ft_strjoin(ret_v, "\n", ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, RED, ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, "└─", ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, string_ternary(ms->l_retv != 0, RED, GREEN), ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, "$ ", ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, RESET, ms);
	ft_free(tmp, ms);
	return (ret_v);
}
