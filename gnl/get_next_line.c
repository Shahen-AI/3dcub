/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:00:19 by ster-min          #+#    #+#             */
/*   Updated: 2021/02/02 17:00:21 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		bsn_len(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i] && str[i] != '\n')
		++i;
	return (i);
}

int		bsn_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

int		ft_output(char *new_line, int st_i)
{
	int i;

	i = 0;
	if (!new_line)
		return (0);
	if (new_line[st_i] == '\n')
		i = 1;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char	*new_line;
	char		*buff;
	ssize_t		ret;
	int			len;
	int			out;

	out = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 ||
	(!(buff = malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		new_line = ft_strjoin_gnl(new_line, buff);
		if (bsn_check(new_line))
			break ;
	}
	free(buff);
	if (ret < 0)
		return (-1);
	len = bsn_len(new_line);
	*line = ft_substr_gnl(new_line, len);
	out = ft_output(new_line, len);
	new_line = get_line_gnl(new_line, len);
	return (out);
}
