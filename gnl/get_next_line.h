/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ster-min <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:00:53 by ster-min          #+#    #+#             */
/*   Updated: 2021/02/02 17:15:43 by ster-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

#define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
char	*get_line_gnl(char *str, int len);
char	*ft_strjoin_gnl(char *string, char *buff);
size_t	ft_strlen(const char *s);
char	*ft_substr_gnl(char const *s, int len);

#endif
