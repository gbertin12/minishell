/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:25:16 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/20 12:27:47 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **tab, t_minishell *ms)
{
	size_t	i;

	i = -1;
	while (tab[i++])
		ft_free(tab[i], ms);
	ft_free(tab, ms);
}
