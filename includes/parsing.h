/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:29:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/22 12:39:31 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

char			parsing(char *s, t_minishell *ms);

long long int	add_arg(char *s, t_token *token, t_minishell *ms);
long long int	add_output(char *s, t_token *token, t_minishell *ms);
long long int	add_input(char *s, t_token *token, t_minishell *ms);

size_t			search_next_sep(char *s);

#endif
