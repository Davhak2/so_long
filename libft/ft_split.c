/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:14 by davihako          #+#    #+#             */
/*   Updated: 2025/02/25 18:24:39 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(const char *s, char c)
{
	size_t	count;
	size_t	is_new;

	count = 0;
	is_new = 1;
	while (*s)
	{
		if (*s != c && is_new)
		{
			is_new = 0;
			++count;
		}
		else if (*s == c && !is_new)
			is_new = 1;
		++s;
	}
	return (count);
}

char	*new_word(const char **s, char c)
{
	char	*end;
	size_t	word_len;
	char	*new_word;

	while (**s == c)
		++*s;
	end = ft_strchr(*s, c);
	if (end)
		word_len = end - *s;
	else
		word_len = ft_strlen(*s);
	new_word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!new_word)
		return (NULL);
	ft_strlcpy(new_word, *s, word_len + 1);
	if (end)
		*s = end;
	return (new_word);
}

static void	free_split(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**words;
	size_t	i;

	if (!s)
		return (NULL);
	count = wordcount(s, c) + 1;
	words = (char **)malloc(count * sizeof(void *));
	if (!words)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		words[i] = new_word(&s, c);
		if (!words[i])
		{
			free_split(&words, i);
			return (NULL);
		}
		++i;
	}
	words[i] = NULL;
	return (words);
}
