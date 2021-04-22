/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:47 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/28 16:01:28 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int len;

	len = 0;
	if (n <= 0)
	{
		++len;
		n *= (-1);
	}
	while (n != 0)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= (-1);
	}
	else if (nbr == 0)
		res[0] = '0';
	res[len] = '\0';
	while (len > 0 && nbr != 0)
	{
		--len;
		res[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (res);
}
