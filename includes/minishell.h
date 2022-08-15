/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:35:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/15 18:28:47 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "structures.h"
# include "../sources/libs/libft/libft.h"
# include "utils.h"

void	free_all(t_minishell *ms);
void	ft_free(void *ptr, t_minishell *ms);
void	add_end_obj(t_obj *head, t_obj *obj);
void	copy_env(t_minishell *ms, char **env);

void	*ft_malloc(size_t size, t_minishell *ms);

#endif
