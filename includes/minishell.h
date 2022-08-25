/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:35:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/25 12:07:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include libs
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include "../sources/libs/libft/libft.h"

//include minishell
# include "structures.h"
# include "utils.h"
# include "built_in.h"
# include "parsing.h"
# include "expand.h"
# include "signals.h"
# include "check.h"
# include "execute.h"

void	copy_env(t_minishell *ms, char **env);

#endif
