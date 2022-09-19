/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:49:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/19 09:36:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_H
# define OPEN_H

int		check_ambiguous(char *path, char *print, int ambiguous);
char	*expand_file(char *path, t_minishell *ms);
char	*simple_var(char *path);
char	*replace_value_file(char *key, t_minishell *ms);
char	*complexe_var(char *path, t_minishell *ms);
char	*get_value_key(char *path, t_minishell *ms);
int		get_size_key(char *path);

void	open_all(t_minishell *ms);

int		have_infile(t_token *token);
int		have_outfile(t_token *token);
int		open_output(t_token *token, t_minishell *ms);
int		open_input(t_token *token, t_minishell *ms);
int		heredoc(char *limiter, t_minishell *ms);

char	did_print(t_file *file, t_file *head);
void	put_error_fd(t_file *file, t_file *head, t_minishell *ms);

#endif