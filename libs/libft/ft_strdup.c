/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:20 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/25 16:39:22 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (s[len])
		++len;
	if (!(res = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (i < len)
	{
		res[i] = s[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
