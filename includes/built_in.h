/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:58:16 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/22 10:21:57 by gbertin          ###   ########.fr       */
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

#endif
