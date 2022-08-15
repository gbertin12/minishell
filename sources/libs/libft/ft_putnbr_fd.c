/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:44:11 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/23 13:44:11 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nbr(unsigned int v, int fd)
{
	if (v < 10)
	{
		v += 48;
		write(fd, &v, 1);
		return ;
	}
	write_nbr(v / 10, fd);
	write_nbr(v % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	v;

	if (n < 0)
	{
		v = -n;
		write(fd, "-", 1);
	}
	else
		v = n;
	write_nbr(v, fd);
}
