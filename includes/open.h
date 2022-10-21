/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:49:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/21 12:37:45 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_H
# define OPEN_H

char	did_print(t_file *file, t_file *head);
char	*simple_var(char *path, t_minishell *ms);
char	*complexe_var(char *path, t_minishell *ms);
char	*get_value_key(char *path, t_minishell *ms);
char	*replace_value_file(char *key, t_minishell *ms);
char	*expand_file(char *path, t_file *file, t_minishell *ms);

void	open_all(t_minishell *ms);
void	heredoc_child(int fd, char *limiter, t_minishell *ms);
void	put_error_fd(t_file *file, t_file *head, t_minishell *ms);

int		get_size_key(char *path);
int		have_infile(t_token *token);
int		have_outfile(t_token *token);
int		heredoc(char *limiter, t_minishell *ms);
int		open_input(t_token *token, t_minishell *ms);
int		open_output(t_token *token, t_minishell *ms);
int		check_have_next_type(t_file *file, char type);
int		check_ambiguous(char *path, char *print, t_file *file, int ambiguous);


#endif
