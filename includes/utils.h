/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:07:10 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/18 11:27:40 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "structures.h"
# include "minishell.h"

size_t	count_env(t_env *ptr);
size_t	count_arg(t_arg *ptr);

char	**env_to_tab(t_minishell *ms);
char	*ft_superjoin(char **s, t_minishell *ms);
char	*env_var_to_value(char *key, t_minishell *ms);

char	do_env_key_exist(char *key, t_minishell *ms);

void	free_all(t_minishell *ms);
void	ft_free(void *ptr, t_minishell *ms);
void	init_minishell(t_minishell *ms);

void	add_end_obj(t_obj *head, t_obj *obj);
void	add_end_token(t_token *obj, t_minishell *ms);
void	add_end_arg(t_arg *head, t_arg *obj);

char	is_space(char c);

void	*ft_malloc(size_t size, t_minishell *ms);

#endif
