/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:34:20 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/27 21:55:28 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) != NULL && s1[i])
		++i;
	while (len > i && ft_strchr(set, s1[len]) != NULL && s1[i])
		--len;
	if (!(res = (char *)malloc(sizeof(char) * (len - i + 2))))
		return (NULL);
	ft_strlcpy(res, s1 + i, len - i + 2);
	return (res);
}
