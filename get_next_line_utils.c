/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuturano <iuturano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:07:42 by iuturano          #+#    #+#             */
/*   Updated: 2022/11/12 14:15:40 by iuturano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*ptr_b;

	ptr_b = b;
	while (len--)
		*ptr_b++ = c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (0);
    ft_memset(ptr, '\0', total_size);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while ((unsigned char) *s != (unsigned char) c)
	{
		if (!(*s))
			return (0);
		s++;
	}
	return ((char *) s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*p_join;

	if (!s1 || !s2)
		return (0);
	join = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!join)
		return (0);
	p_join = join;
	while (*s1)
		*p_join++ = *s1++;
	while (*s2)
		*p_join++ = *s2++;
	return (join);
}