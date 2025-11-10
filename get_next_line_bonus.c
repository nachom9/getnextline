/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imelero- <imelero-@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:09:15 by imelero-          #+#    #+#             */
/*   Updated: 2025/10/22 15:58:30 by imelero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_get_big(char *buffer, char **big)
{
	char	*tmp;

	if (!*big)
		*big = ft_strdup(buffer);
	else if (buffer)
	{
		tmp = *big;
		*big = ft_strjoin(*big, buffer);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
}

static char	*ft_get_line(char **big)
{
	char	*result;
	char	*str;
	char	*new_big;

	str = ft_strchr(*big, '\n');
	if (str)
	{
		new_big = ft_strdup(str + 1);
		result = ft_substr(*big, 0, str - *big + 1);
		if (big)
			free (*big);
		*big = new_big;
	}
	else
	{
		result = ft_strdup(*big);
		if (*big)
		{
			free(*big);
			*big = NULL;
		}
	}
	return (result);
}

static char	*ft_free(char **big, char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (*big && **big != '\0')
		return (ft_get_line(big));
	if (*big)
	{
		free (*big);
		*big = NULL;
	}
	return (NULL);
}

static char	*ft_result(char **big, char *buffer, int fd)
{
	int			bytes;
	char		*line;

	while (!*big || !ft_strchr(*big, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			if (*big)
			{
				free(*big);
				*big = NULL;
			}
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (bytes == 0)
			return (ft_free(big, buffer));
		ft_get_big (buffer, big);
	}
	free(buffer);
	return (line = ft_get_line(big), line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*big[1024];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = ft_result(&big[fd], buffer, fd);
	return (line);
}
