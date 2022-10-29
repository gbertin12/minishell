/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:18:19 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/29 20:39:22 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

void	delete_quotes(t_token *token, t_minishell *ms);
void	remove_null(t_token *token, t_minishell *ms);

char	*read_var(char *s, t_minishell *ms);
char	*heredoc_expand(char *s, t_minishell *ms);
char	*keep_left(t_arg *arg, char *w, t_minishell *ms);	
char	*replace_var(char *s, size_t x, t_minishell *ms);
char	*replace_var_multi(char *s, size_t x, char *value, t_minishell *ms);
char	*remove_quotes(char *s, t_minishell *ms, int depth);

char	expand(t_minishell *ms);
char	expand_arg(t_token *token, t_minishell *ms);
char	expand_cmd(t_token *token, t_minishell *ms);

#endif
