/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:15 by davihako          #+#    #+#             */
/*   Updated: 2025/01/12 16:32:58 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	s_len;
	char	letter;

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
