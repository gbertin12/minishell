/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:58:16 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/29 11:00:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"

char	_cd(t_token *token, t_minishell *ms);
int		_env(t_minishell *ms);
int		_export(t_token *token, t_minishell *ms);
int		_pwd(t_token *token);
int		_unset(char *key, t_minishell *ms);
int		_echo(t_token *token);
int		b_exit(t_token *token, t_minishell *ms);

int		exec_env(t_token *token, t_minishell *ms);
int		exec_pwd(t_token *token);
int		exec_cd(t_token *token, t_minishell *ms);
int		exec_echo(t_token *token);
int		exec_export(t_token *token, t_minishell *ms);
int		exec_unset(t_token *token, t_minishell *ms);

int		check_is_built_in(t_token *token, t_minishell *ms);
int		exec_env(t_token *token, t_minishell *ms);

#endif