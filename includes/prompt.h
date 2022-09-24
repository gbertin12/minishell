/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:47:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/30 12:17:01 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "structures.h"
# include <stddef.h>
# include "../sources/libs/libft/libft.h"
//colors
# define BLUE "\033[036m"
# define RED "\033[031m"
# define GREEN "\033[032m"
# define YELLOW "\033[033m"
# define PURPLE "\033[035m"
# define LIGHTPURPLE "\033[034m"
# define WHITE "\033[037m"
# define RESET "\033(B\033[m"

char	*get_prompt(t_minishell *ms);

#endif
