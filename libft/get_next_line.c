/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luminous <luminous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:09:41 by davihako          #+#    #+#             */
/*   Updated: 2025/03/18 23:59:16 by luminous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_buff(char *buff1, char *buff2)
{
	char	*res;

	res = ft_strjoin_gnl(buff1, buff2);
	if (!res)
	{
		free(buff1);
		return (NULL);
	}
	free(buff1);
	return (res);
}

char	*next(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	line = ft_calloc_gnl(ft_strlen_gnl(buff) - i, sizeof(char));
	if (!line)
	{
		free(buff);
		return (NULL);
	}
	i++;
	j = 0;
	while (buff[i])
		line[j++] = buff[i++];
	line[j] = '\0';
	free(buff);
	return (line);
}

char	*buff_line(char *buff)
{
	int		count;
	char	*res;

	count = 0;
	while (buff[count] && buff[count] != '\n')
		count++;
	if (buff[count] == '\n')
		res = ft_calloc_gnl(count + 2, sizeof(char));
	else
		res = ft_calloc_gnl(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	count = 0;
	while (buff[count] && buff[count] != '\n')
	{
		res[count] = buff[count];
		count++;
	}
	if (buff[count] == '\n')
		res[count] = '\n';
	return (res);
}

char	*read_file(int fd, char *res)
{
	char	*buff;
	int		bytes;

	if (!res)
		res = ft_calloc_gnl(1, sizeof(char));
	buff = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	bytes = read(fd, buff, BUFFER_SIZE);
	while (bytes > 0)
	{
		buff[bytes] = '\0';
		res = free_buff(res, buff);
		if (ft_strchr_gnl(buff, '\n'))
			break ;
		bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (bytes < 0 || !res[0])
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = read_file(fd, buff);
	if (!buff)
		return (NULL);
	line = buff_line(buff);
	buff = next(buff);
	return (line);
}
