/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:58:16 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/06 14:59:30 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

char	_cd(t_token *token, t_minishell *ms);
int		_env(t_minishell *ms);
int		_export(t_token *token, t_minishell *ms);
int		_pwd(t_token *token);
int		_unset(char *key, t_minishell *ms);
int		_echo(t_token *token);
int		b_exit(t_token *token, t_minishell *ms);

int		check_is_built_in(t_token *token);
int		exec_builtin(t_token *token, t_minishell *ms);
int		exec_env(t_token *token, t_minishell *ms);

#endif
