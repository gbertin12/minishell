/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:18:19 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/03 13:35:04 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

void	delete_quotes(t_token *token, t_minishell *ms);
void	remove_null(t_token *token, t_minishell *ms);

char	*read_var(char *s, t_minishell *ms);
char	*heredoc_expand(char *s, t_minishell *ms);
char	*replace_var(char *s, size_t x, t_minishell *ms);

char	expand(t_minishell *ms);
char	expand_arg(t_token *token, t_minishell *ms);
char	expand_cmd(t_token *token, t_minishell *ms);
#endif
