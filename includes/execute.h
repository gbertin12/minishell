/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:40:09 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/30 12:10:12 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

char	**get_path_env(t_minishell *ms);
char	*make_path(t_exec *exec, t_minishell *ms);

int		ft_search_char(char *str);
int		browse_cmd(t_minishell *ms);

int		have_infile(t_token *token);
int		have_outfile(t_token *token);
int		open_output(t_token *token);
int		open_input(t_token *token);

int		init_execute(t_token *token);
int		redir_in(t_token *token, t_token *last);
int		redir_out(t_token *token);

int		exec_cd(t_token *token, t_minishell *ms);
int		exec_env(t_token *token, t_minishell *ms);
int		exec_export(t_token *token, t_minishell *ms);
int		exec_unset(t_token *token, t_minishell *ms);
int		exec_pwd(t_token *token);
int		exec_echo(t_token *token);

int		exec_first_cmd(t_exec *exec, t_minishell *ms);
int		exec_middle(char **args, t_exec *exec, t_minishell *ms);
int		exec_last(char **args, t_exec *exec, t_minishell *ms);
int		execute_cmd(t_token *token, int pipefd[2], char **args,
			t_minishell *ms);

t_exec	*first(t_exec *exec, t_minishell *ms);
t_exec	*middle(t_exec *exec, t_minishell *ms);
t_exec	*last(t_exec *exec, t_minishell *ms);

#endif
