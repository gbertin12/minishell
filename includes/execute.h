/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:40:09 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/25 13:46:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "minishell.h"

char	**get_path_env(t_minishell *ms);
int		ft_search_char(char *str);
char	*make_path(t_token *token, t_minishell *ms);
int		init_execute(t_token *token, t_minishell *ms);
int		execute_cmd(t_token *token, int pipefd[2], char **args, t_minishell *ms);
int		browse_cmd(t_minishell *ms);

int		open_input(t_token *token, t_minishell *ms);
int		open_output(t_token *token);
int		have_infile(t_token *token);
int		have_outfile(t_token *token);

int		redir_out(t_token *token);
int		redir_in(t_token *token, t_token *last);

#endif