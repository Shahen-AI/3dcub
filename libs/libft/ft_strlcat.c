/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:29 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/25 16:39:32 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t d_len;
	size_t s_len;

	d_len = 0;
	i = 0;
	s_len = 0;
	while (*(dest + d_len) && d_len < size)
		++d_len;
	while (*(src + s_len))
		++s_len;
	while (d_len + i + 1 < size && *(src + i))
	{
		*(dest + d_len + i) = *(src + i);
		++i;
	}
	if (i != 0)
		*(dest + d_len + i) = '\0';
	return (s_len + d_len);
}
