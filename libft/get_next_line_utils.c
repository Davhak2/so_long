/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luminous <luminous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:07:54 by davihako          #+#    #+#             */
/*   Updated: 2025/03/19 00:00:13 by luminous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	s_len;
	char	letter;

	if (!s)
		return (NULL);
	letter = (char)c;
	s_len = ft_strlen(s) + 1;
	while (s_len--)
	{
		if (*s == letter)
			return ((char *)s);
		++s;
	}
	return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	const char	*str1;

	if (!str)
		return (0);
	str1 = str;
	while (*str)
		str++;
	return (str - str1);
}

char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	int		size;
	char	*res;
	char	*start;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	start = res;
	if (s1)
		while (*s1)
			*(res++) = *(s1++);
	if (s2)
		while (*s2)
			*(res++) = *(s2++);
	*res = '\0';
	return (start);
}

void	*ft_memset_gnl(void *b, int c, size_t len)
{
	unsigned char	*mem;

	mem = (unsigned char *)b;
	while (len--)
		*mem++ = (unsigned char)c;
	return (b);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(1));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset_gnl(ptr, 0, count * size);
	return (ptr);
}
