/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:37 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/15 16:34:17 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_file
{
	char			*path;
	int				*fd;
	char			exist;
	struct s_file	*next;
}	t_file;

typedef struct s_arg
{
	char			*arg;
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
	struct s_arg	*arg_head;
	struct s_token	*next;
}	t_token;

typedef struct s_obj
{
	void			*ptr;
	struct s_obj	*next;
}	t_obj;

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