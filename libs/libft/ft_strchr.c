/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:03 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/25 16:39:05 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	symb;

	symb = c;
	i = 0;
	if (symb == '\0')
	{
		while (*(s + i))
			++i;
		return (char *)(s + i);
	}
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == symb)
			return ((char *)(s + i));
		++i;
	}
	return (NULL);
}
