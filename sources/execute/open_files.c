/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:27:30 by gbertin           #+#    #+#             */
/*   Updated: 2022/09/01 13:26:43 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_have_next_type(t_file *file, int type)
{
	if (!file->next)
		return (1);
	while (file)
	{
		if (file->type == type)
			return (0);
		file = file->next;
	}
	return (1);
}

int	heredoc(char *limiter, t_minishell *ms)
{
	char	*append;
	int		fd;
	int		pid;

	fd = open(".tmp", O_TRUNC | O_CREAT | O_RDWR , 0644);
	if (fd < 0)
		return (fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		append = readline(">");
		while (!ft_strcmp(append, limiter))
		{
			append = heredoc_expand(append, ms);
			ft_putstr_fd(append, fd);
			ft_putstr_fd("\n", fd);
			free(append);
			append = readline(">");
		}
		free(append);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	return (fd);
}

static void	put_error_fd(t_file *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	ft_putchar_fd('\n', 2);
}

int	open_output(t_token *token)
{
	t_file	*file;
	int		fd;

	file = token->file_head;
	fd = 1;
	while (file)
	{
		if (fd > 0 && fd != 1)
			close(fd);
		if (!file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
			fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			put_error_fd(file);
		if (check_have_next_type(file, 1))
			return (fd);
		file = file->next;
	}
	return (fd);
}

int	open_input(t_token *token, t_minishell *ms)
{
	t_file	*file;
	int		fd;

	file = token->file_head;
	fd = 1;
	while (file)
	{
		if (fd > 0 && fd != 1)
			close(fd);
		if (file->type)
		{
			file = file->next;
			continue ;
		}
		if (file->append)
			fd = heredoc(file->path, ms);
		else
			fd = open(file->path, O_RDONLY, 0644);
		if (fd < 0)
			put_error_fd(file);
		if (check_have_next_type(file, 0))
			return (fd);
		file = file->next;
	}
	return (fd);
}
