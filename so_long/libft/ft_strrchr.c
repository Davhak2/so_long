/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:35 by davihako          #+#    #+#             */
/*   Updated: 2025/01/12 16:34:04 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*iter;
	size_t	s_len;
	char	letter;

	s_len = ft_strlen(s) + 1;
	iter = NULL;
	letter = (char)c;
	while (s_len--)
	{
		if (*s == letter)
			iter = (char *)s;
		++s;
	}
	return (iter);
}
