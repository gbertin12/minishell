/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:10:08 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/24 18:07:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(t_minishell *ms)
{
	char	*v_print;
	char	*v_ret;

	v_print = NULL;
	v_ret = NULL;
	v_print = getcwd(NULL, 0);
	if (v_print == NULL)
		strerror(errno);
	v_ret = ft_strdup(v_print, ms);
	free(v_print);
	return (v_ret);
}
