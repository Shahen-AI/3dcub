/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:46:14 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/27 21:14:28 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	index;
	size_t	s_len;
	size_t	over_len;

	index = 0;
	if (!s)
		return (NULL);
	over_len = ft_strlen(s + start);
	if (len > over_len)
		len = over_len;
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (!(res = (char *)malloc((len + 1) * sizeof(*res))))
		return (NULL);
	while (index < len && start + index < s_len)
	{
		*(res + index) = *(s + start + index);
		++index;
	}
	*(res + len) = '\0';
	return (res);
}
