/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:21:24 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/08 16:21:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long unsigned int	ft_pow(int v, int pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	return (v * ft_pow(v, pow - 1));
}

static char	*ft_itoa_part2(int len, int n, unsigned int x, char *v)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	len --;
	if (n < 0)
	{
		v[0] = '-';
		i++;
		len--;
	}
	while (len >= 0)
	{
		y = x / ft_pow(10, len);
		v[i] = (y + '0');
		v[i + 1] = 0;
		x %= ft_pow(10, len);
		len--;
		i++;
	}
	return (v);
}

char	*ft_itoa(int n, t_minishell *ms)
{
	int					len;
	unsigned int		x;
	char				*v;

	len = 1;
	if (n < 0)
		x = -n;
	else
		x = n;
	while (x % ft_pow(10, len) != x)
		len++;
	if (n < 0)
		len++;
	v = ft_malloc(len + 1, ms);
	if (v == NULL)
		return (NULL);
	return (ft_itoa_part2(len, n, x, v));
}
