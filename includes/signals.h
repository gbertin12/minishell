/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:19:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/25 16:41:30 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		init_signals(void);
void		sigint_heredoc(int sig);

extern char	g_mode;
#endif
