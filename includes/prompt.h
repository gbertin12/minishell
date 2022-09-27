/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:47:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/24 12:45:18 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "structures.h"
# include <stddef.h>
# include "../sources/libs/libft/libft.h"
//colors
# define BLUE "\1\e[0;36m\2"
# define RED "\1\e[0;31m\2"
# define GREEN "\1\e[0;32m\2"
# define YELLOW "\1\e[0;33m\2"
# define PURPLE "\1\e[0;35m\2"
# define LIGHTPURPLE "\1\e[0;34m\2"
# define WHITE "\1\e[0;37m\2"
# define RESET "\1\e[0m\2"

char	*get_prompt(t_minishell *ms);

#endif
