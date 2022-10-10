/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/10 16:16:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_minishell	t_minishell;

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

/* 
 * @param t_head head of token list from parsing
 * @param o_head head of objects list from ft_malloc
 * @param l_retv last return value returned from tokens
 * @param e_head head of env list from exports
 * @param l_input last input
 */

typedef struct s_minishell
{
	t_token			*t_head;
	struct s_obj	*o_head;
	int				l_retv;
	t_env			*e_head;
	char			*l_input;
	t_file_error	*err_head;
	char			*pwd;
	t_exec			*exec;
	char			*s;
}	t_minishell;

typedef struct s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}	t_heredoc;

#endif
