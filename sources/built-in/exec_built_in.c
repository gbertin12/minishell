/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:39:59 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/02 17:04:55 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_built_in(t_token *token)
{
	if (ft_strcmp(token->cmd, "env"))
		return (1);
	if (ft_strcmp(token->cmd, "pwd"))
		return (1);
	if (ft_strcmp(token->cmd, "cd"))
		return (1);
	if (ft_strcmp(token->cmd, "echo"))
		return (1);
	if (ft_strcmp(token->cmd, "export"))
		return (1);
	if (ft_strcmp(token->cmd, "unset"))
		return (1);
	return (0);
}

int	exec_builtin(t_token *token, t_minishell *ms)
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
