/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:07:10 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/15 18:29:58 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "structures.h"
# include "minishell.h"

size_t	count_env(t_env *ptr);

char	**env_to_tab(t_minishell *ms);

#endif
