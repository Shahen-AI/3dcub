/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:36:56 by ster-min          #+#    #+#             */
/*   Updated: 2021/01/25 16:37:00 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *res;

	if (!(res = ((void *)malloc(nmemb * size))))
		return (NULL);
	ft_bzero(res, size * nmemb);
	return (res);
}
