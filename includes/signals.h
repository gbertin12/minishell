/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:19:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/08/30 12:12:51 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		init_signals(void);
void		sigint_heredoc(int sig);

extern char	g_mode;
#endif
