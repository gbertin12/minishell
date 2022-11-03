/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:35:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/03 14:39:34 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_heredoc(char *limiter, int fd)
{
	ft_putstr_fd("minishell: warning: here-document delimited by\
 end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	return (fd);
}

// static void	free_append(void *append, t_minishell *ms)
// {
// 	t_obj	*x;
// 	t_obj	*last;

// 	last = NULL;
// 	x = ms->o_head;
// 	while (x != NULL)
// 	{
// 		if (&x->ptr == &append)
// 		{
// 			free(append);
// 			if (last == NULL)
// 				ms->o_head = x->next;
// 			else
// 				last->next = x->next;
// 			free(x);
// 			return ;
// 		}
// 		last = x;
// 		x = x->next;
// 	}
// 	free(append);
// }

static int	print_in_file2(int fd, char *append, char *limiter, int *err)
{
	if (append)
	{
		ft_putstr_fd(append, fd);
		ft_putstr_fd("\n", fd);
	}
	else if (!append)
	{
		*err = 130;
		if (g_lretv != 130)
			*err = error_heredoc(limiter, fd);
		return (1);
	}
	return (0);
}

static int	print_in_file(int fd, char *limiter, t_minishell *ms)
{
	char	*append;
	int		err;
	char	*tmp;

	err = 0;
	signal(SIGINT, sigint_heredoc);
	tmp = readline("> ");
	append = ft_strdup(tmp, ms);
	free(tmp);
	while (!ft_strcmp(append, limiter))
	{
		append = heredoc_expand(append, ms);
		ft_free(append, ms);
		if (print_in_file2(fd, append, limiter, &err))
			break ;
		tmp = readline("> ");
		append = ft_strdup(tmp, ms);
		free(tmp);
	}
	return (ft_free(append, ms), err);
}

void	heredoc_child(int fd, char *limiter, t_minishell *ms)
{
	int	ret;

	signal(SIGINT, sigint_heredoc);
	rl_clear_history();
	g_lretv = 0;
	ret = print_in_file(fd, limiter, ms);
	close(fd);
	exit_child(ret, ms);
}
