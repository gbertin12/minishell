/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:17 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/06 14:12:43 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/prompt.h"

static char	*get_prompt2(t_minishell *ms, char *pwd, char *ret_v, char *tmp)
{
	ret_v = ft_strjoin(tmp, BLUE, ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, pwd, ms);
	ft_free(pwd, ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, string_ternary(ms->l_retv != 0, RED, GREEN), ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, "$ ", ms);
	ft_free(ret_v, ms);
	ret_v = ft_strjoin(tmp, RESET, ms);
	ft_free(tmp, ms);
	return (ret_v);
}

char	*get_prompt(t_minishell *ms)
{
	char	*ret_v;
	char	*tmp;
	char	*pwd;
	char	*user;

	if (do_env_key_exist("PS1", ms))
		return (get_env_value("PS1", ms));
	user = ft_strdup("minishell", ms);
	pwd = get_pwd(ms);
	tmp = ft_strjoin(GREEN, user, ms);
	ft_free(user, ms);
	ret_v = ft_strjoin(tmp, WHITE, ms);
	ft_free(tmp, ms);
	tmp = ft_strjoin(ret_v, ":", ms);
	return (get_prompt2(ms, pwd, ret_v, tmp));
}
