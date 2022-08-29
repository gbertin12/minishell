/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/29 13:04:51 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_minishell	t_minishell;

typedef struct s_file
{
	char			*path;
	int				*fd;
	char			type;
	char			append;
	char			exist;
	char			apos;
	struct s_file	*next;
}	t_file;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;	
	char			apos;
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
	char	**path_absolute;
}	t_exec;

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
}	t_minishell;

#endif
