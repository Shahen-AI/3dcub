/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:25:27 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/21 20:39:46 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *source;
	size_t				index;

	index = 0;
	source = (const unsigned char *)s;
	while (index < n)
	{
		if (*(source + index) == (unsigned char)c)
			return ((void *)s + index);
		++index;
	}
	return (NULL);
}
