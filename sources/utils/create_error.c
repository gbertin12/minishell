/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:13:23 by ccambium          #+#    #+#             */
/*   Updated: 2022/09/13 14:14:20 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\n', 2);
}
