/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmelero <nmelero@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:41:35 by nmelero           #+#    #+#             */
/*   Updated: 2025/10/21 04:39:40 by nmelero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_line(char **big)
{
	char	*line;
	char	*new_big;
	char	*result;

	line = ft_strchr(*big, '\n');
	if (line)
	{
		new_big = ft_strdup(line + 1);
		result = ft_substr(*big, 0, line - *big + 1);
		free(*big);
		*big = new_big;
		return (result);
	}
	else
	{
		result = ft_strdup(*big);
		free(*big);
		*big = NULL;
		return (result);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	char		*tmp;
	static char	*big;
	int			bytes;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
		return (free(big), NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(big, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
		{
			free(buffer);
			if (big && *big)
				return ft_line(&big);
			free(big);
			big = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		tmp = big;
		big = ft_strjoin(big, buffer);
		free(tmp);
	}
	free(buffer);
	line = ft_line(&big);
	return (line);
}
/*
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	free(line);
	close(fd);
	get_next_line(-1);
	return (0);
}*/
