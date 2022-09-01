/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:18:19 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/01 13:27:36 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

void	expand(t_minishell *ms);
void	delete_quotes(t_token *token, t_minishell *ms);

char	*heredoc_expand(char *s, t_minishell *ms);
char	*replace_var(char *s, size_t x, t_minishell *ms);
#endif
