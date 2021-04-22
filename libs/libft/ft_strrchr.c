/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:10 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/25 16:39:12 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	symb;

	symb = c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (*(s + i) == symb)
			return ((char *)(s + i));
		--i;
	}
	return (NULL);
}
