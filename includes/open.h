/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:49:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/15 08:59:51 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_H
# define OPEN_H

int		check_ambiguous(char *path, char *print, t_minishell *ms);
char	*expand_file(char *path, t_minishell *ms);

void	open_all(t_minishell *ms);

int		have_infile(t_token *token);
int		have_outfile(t_token *token);
int		open_output(t_token *token, t_minishell *ms);
int		open_input(t_token *token, t_minishell *ms);
int		heredoc(char *limiter, t_minishell *ms);

char	did_print(t_file *file, t_file *head);
void	put_error_fd(t_file *file, t_file *head, t_minishell *ms);

#endif