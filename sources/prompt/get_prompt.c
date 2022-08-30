/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:17 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/29 12:48:22 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/prompt.h"

static char	*get_prompt3(t_minishell *ms, char *ret_v, char *tmp)
{
	tmp = ft_strjoin(ret_v, YELLOW, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, "]", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, "\n", ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, BLUE, ms);
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

static char	*get_prompt2(t_minishell *ms, char *pwd, char *ret_v, char *tmp)
{
	ret_v = ft_strjoin(tmp, ")", ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, BLUE, ms);
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
	return (get_prompt3(ms, ret_v, tmp));
}

char	*get_prompt(t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	char	*pwd;
	char	*user;

	pwd = NULL;
	user = ft_strdup("minishell", ms);
	pwd = getcwd(NULL, 0);
	ret_v = ft_strjoin(BLUE, "┌──", ms);
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
	return (get_prompt2(ms, pwd, ret_v, tmp));
}
