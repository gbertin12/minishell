/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/28 09:25:15 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <termios.h>

typedef struct s_minishell	t_minishell;
typedef struct termios		t_termios;

typedef struct s_file
{
	char			*path;
	char			type;
	char			append;
	struct s_file	*next;
}	t_file;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}	t_arg;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			show;
	struct s_env	*next;	
}	t_env;

typedef struct s_token
{
	char			*cmd;
	int				pid;
	int				pipefd[2];
	int				have_in;
	int				have_out;
	int				inputfile;
	int				outputfile;
	t_file			*file_head;
	struct s_arg	*arg_head;
	struct s_token	*next;
}	t_token;

typedef struct s_obj
{
	void			*ptr;
	struct s_obj	*next;
}	t_obj;

typedef struct s_exec
{
	int		err;
	int		tmpin;
	int		tmpout;
	t_token	*token;
	t_token	*last;
	char	*path;
	char	**env;
	char	**args;
	int		l_retv;
	char	**path_absolute;
}	t_exec;

typedef struct s_file_error
{
	char					*err;
	struct s_file_error		*next;
}	t_file_error;

typedef struct s_minishell
{
	char			*s;
	char			*l_input;
	char			*pwd;
	t_env			*e_head;
	t_exec			*exec;
	t_token			*t_head;
	t_termios		term;
	t_termios		old_term;
	struct s_obj	*o_head;
	t_file_error	*err_head;
	int				tester;
}	t_minishell;

typedef struct s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}	t_heredoc;

#endif
