/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:48:32 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/27 21:16:22 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	n;
	size_t	m;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1);
	m = ft_strlen(s2);
	if (!(res = (char *)malloc((n + m + 1) * sizeof(*res))))
		return (NULL);
	ft_strlcpy(res, s1, n + 1);
	ft_strlcat(res, s2, m + n + 1);
	return (res);
}
