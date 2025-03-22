/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:34 by davihako          #+#    #+#             */
/*   Updated: 2025/01/19 21:05:24 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *key, size_t len)
{
	size_t	keylen;

	if (!(*key))
		return ((char *)str);
	if (len == 0)
		return (NULL);
	keylen = ft_strlen(key);
	while (*str && len >= keylen)
	{
		if (*str == *key && ft_strncmp(str, key, keylen) == 0)
			return ((char *)str);
		++str;
		--len;
	}
	return (NULL);
}
