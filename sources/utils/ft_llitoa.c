/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:27:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/26 16:39:51 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_countc(long long int n)
{
	int	len;

	len = 0;
	if (n == -9223372036854775807)
		return (20);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

long long	ft_lliota(long long n, t_minishell *ms)
{
	char			*s;
	unsigned int	len;

	len = ft_countc(n);
	if (n == -9223372036854775807)
		return (ft_strdup("-9223372036854775807", ms));
	s = ft_malloc(sizeof(char *), ms);
	if (!s)
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (s);
}