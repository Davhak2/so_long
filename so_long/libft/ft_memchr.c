/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:41:53 by davihako          #+#    #+#             */
/*   Updated: 2025/01/14 16:00:26 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	letter;

	letter = (char)c;
	while (n--)
	{
		if (*(char *)s == letter)
			return ((void *)s);
		s = (char *)s + 1;
	}
	return (NULL);
}
