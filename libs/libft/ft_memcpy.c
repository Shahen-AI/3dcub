/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:21:56 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/20 20:58:08 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char *s;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		++i;
	}
	return (dst);
}
