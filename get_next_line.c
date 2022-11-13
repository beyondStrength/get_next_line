/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuturano <iuturano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:15:35 by iuturano          #+#    #+#             */
/*   Updated: 2022/11/12 18:16:52 by iuturano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	char	*line;
	char	*line_p;
	char	*buffer_p;

	buffer_p = buffer;
	while (*buffer_p && *buffer_p != '\n')
		buffer_p++;
	if (!*buffer_p)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer_p++) + 1), sizeof(char));
	line_p = line;
	while (*buffer_p)
		*line++ = *buffer_p++;
	free(buffer);
	return (line_p);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	char	*line_p;
	char	*buffer_p;

	buffer_p = buffer;
	if (!*buffer)
		return (NULL);
	while (*buffer && *buffer != '\n')
		buffer++;
	line = ft_calloc((buffer - buffer_p) + 2, sizeof(char));
	line_p = line;
	buffer = buffer_p;
	while (*buffer && *buffer != '\n')
		*line++ = *buffer++;
	if (*buffer && *buffer == '\n')
		*line++ = '\n';
	return (line_p);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0;
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
