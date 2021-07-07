/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:00:40 by ster-min          #+#    #+#             */
/*   Updated: 2021/02/02 17:00:42 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		++i;
	return (i);
}

char	*ft_strjoin_gnl(char *string, char *buff)
{
	char	*res;
	int		i;
	int		j;

	if (!(res = malloc(sizeof(char) *
					(ft_strlen(string) + ft_strlen(buff) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	if (string)
		while (string[i])
			res[j++] = string[i++];
	i = 0;
	if (buff)
		while (buff[i])
			res[j++] = buff[i++];
	res[j] = '\0';
	free(string);
	return (res);
}

char	*ft_substr_gnl(char const *s, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		res[i] = s[i];
		++i;
	}
	res[len] = '\0';
	return (res);
}

char	*get_line_gnl(char *str, int len)
{
	char	*temp;
	int		i;
	int		n;

	n = ft_strlen(str);
	i = 0;
	if (!str)
		return (NULL);
	if (str[len] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (!(temp = malloc(n - len + 1)))
		return (NULL);
	while (str[len + i + 1] != '\0')
	{
		temp[i] = str[i + len + 1];
		++i;
	}
	temp[i] = '\0';
	free(str);
	return (temp);
}
