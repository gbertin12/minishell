/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/17 15:05:20 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_minishell	t_minishell;

typedef struct s_file
{
	char			*path;
	int				*fd;
	char			append;
	char			exist;
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
	t_file			*input_head;
	t_file			*output_head;
	int				pipefd[2];
	struct s_arg	*arg_head;
	struct s_token	*next;
}	t_token;

typedef struct s_obj
{
	void			*ptr;
	struct s_obj	*next;
}	t_obj;

typedef struct s_builtin
{
	char				*name;
	int					(*f)(struct s_token, struct s_minishell);
	struct s_builtin	*next;
}	t_builtin;

/* 
 *  @param t_head head of token list from parsing
 *  @param o_head head of objects list from ft_malloc
 *  @param l_retv last return value returned from tokens
 *  @param e_head head of env list from exports
 */

typedef struct s_minishell
{
	t_token			*t_head;
	struct s_obj	*o_head;
	int				l_retv;
	t_env			*e_head;
	char			*l_input;
}	t_minishell;

#endif
