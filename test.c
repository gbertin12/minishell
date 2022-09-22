/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:32:13 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/18 12:11:24 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char 			*path;
	DIR				*dir;
	struct dirent	*read_dir;

	// path = getcwd(path, 0);
	// printf("%s\n", path);
	// dir = opendir("../");
	// read_dir = readdir(dir);
	// while(read_dir)
	// {
	// 	printf("File : %s\n", read_dir->d_name);
	// 	read_dir = readdir(dir);
	// }
	// closedir(dir);
	chdir("../");
	return (0);
}