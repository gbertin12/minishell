/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:14:40 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/22 14:35:04 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".../../includes/minishell.h"

int	check_access()
{
	
	return (0);
}
int	execute_cmd(t_token *token, t_minishell *ms)
{
		
}

int	browse_cmd(t_minishell *ms)
{
	t_token	*token;

	ms->path_absolute = get_path_absolute(ms);
	while (token)
	{
		execute_cmd(token, ms);
		token = token->next;
	}
}
