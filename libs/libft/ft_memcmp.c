/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:42:00 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/21 20:54:26 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *string1;
	const unsigned char *string2;
	size_t				index;

	index = 0;
	string1 = s1;
	string2 = s2;
	while (index < n)
	{
		if (*(string1 + index) != *(string2 + index))
			return (*(string1 + index) - *(string2 + index));
		++index;
	}
	return (0);
}
