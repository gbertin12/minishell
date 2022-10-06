/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:29:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/06 10:33:19 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

char			check_input(t_token *head, char *s);
char			parsing(char *s, t_minishell *ms);

long long int	add_arg(char *s, t_token *token, t_minishell *ms);
long long int	add_output(char *s, t_token *token, t_minishell *ms);
long long int	add_input(char *s, t_token *token, t_minishell *ms);

size_t			search_next_sep(char *s);

#endif
