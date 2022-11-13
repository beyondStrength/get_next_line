/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuturano <iuturano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:15:35 by iuturano          #+#    #+#             */
/*   Updated: 2022/11/13 15:41:23 by iuturano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char *buffer);
static char	*ft_line(char *buffer);
static char	*read_file(int fd, char *file_read);
static char	*ft_free(char *buffer, char *buf);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (0);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*ft_next(char *buffer)
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
		return (0);
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
		return (0);
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

static char	*read_file(int fd, char *file_read)
{
	char	*buffer;
	int		bytes;

	if (!file_read)
		file_read = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[bytes] = 0;
		file_read = ft_free(file_read, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (file_read);
}
