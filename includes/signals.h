/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:19:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/10/17 11:11:03 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void		init_signals(void);
void		exec_signals(void);
void		sigint_exec(int sig);
void		sigquit_exec(int sig);
void		sigint_handler(int sig);
void		sigint_heredoc(int sig);
void		sigquit_handler(int sig);

#endif
