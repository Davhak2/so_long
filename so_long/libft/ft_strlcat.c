/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:24 by davihako          #+#    #+#             */
/*   Updated: 2025/01/12 16:27:46 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = ft_strlen(src);
	i = 0;
	while (*dest)
	{
		dest++;
		len1++;
	}
	if (size == 0 || size <= len1)
		return (size + len2);
	while (*src && i < size - len1 - 1)
	{
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (len1 + len2);
}
