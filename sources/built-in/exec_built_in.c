/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:39:59 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/29 11:00:47 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_built_in(t_token *token, t_minishell *ms)
{
	if (ft_strcmp(token->cmd, "env"))
		return (exec_env(token, ms));
	if (ft_strcmp(token->cmd, "pwd"))
		return (exec_pwd(token));
	if (ft_strcmp(token->cmd, "cd"))
		return (exec_cd(token, ms));
	if (ft_strcmp(token->cmd, "echo"))
		return (exec_echo(token));
	if (ft_strcmp(token->cmd, "export"))
		return (exec_export(token, ms));
	if (ft_strcmp(token->cmd, "unset"))
		return (exec_unset(token, ms));
	return (0);
}
