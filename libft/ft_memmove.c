/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:00 by davihako          #+#    #+#             */
/*   Updated: 2025/01/12 17:23:48 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*iter_dest;

	if (dest != src && n)
	{
		iter_dest = (unsigned char *)dest;
		if (dest < src)
			while (n--)
				*iter_dest++ = *(const unsigned char *)src++;
		else
		{
			iter_dest += n;
			src = (const unsigned char *)src + n;
			while (n--)
				*--iter_dest = *(const unsigned char *)--src;
		}
	}
	return (dest);
}
