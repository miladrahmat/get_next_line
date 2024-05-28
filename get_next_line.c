/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:14 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/05/28 20:01:10 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_free(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*read_line(int fd, char *result)
{
	char	*buffer;
	char	*temp;
	ssize_t	check;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(result, '\n') == 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
			return (ft_free(&buffer));
		if (check == 0)
			break ;
		buffer[check] = '\0';
		temp = result;
		result = ft_strjoin(result, buffer);
		ft_free(&temp);
		if (result == NULL)
			return (ft_free(&buffer));
	}
	ft_free(&buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*line;
	char			*temp;
	size_t			len;
	size_t			len_nl;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (remainder != NULL)
			ft_free(&remainder);
		return (NULL);
	}
	line = (char *)malloc(1 * sizeof(char));
	if (line == NULL)
		return (NULL);
	*line = '\0';
	if (remainder != NULL)
	{
		temp = line;
		line = ft_strjoin(line, remainder);
		ft_free(&temp);
		ft_free(&remainder);
		if (line == NULL)
			return (NULL);
	}
	line = read_line(fd, line);
	if (line == NULL)
	{
		if (remainder != NULL)
			return (ft_free(&remainder));
		return (NULL);
	}
	len = ft_strlen(line);
	if (len == 0)
		return (ft_free(&line));
	len_nl = ft_strlen_nl(line);
	if (len != len_nl)
	{
		remainder = ft_substr(line, len_nl + 1, len - len_nl - 1);
		if (remainder == NULL)
			return (ft_free(&line));
		line[len_nl + 1] = '\0';
	}
	return (line);
}
/* 
#include <stdio.h>
#include <fcntl.h>
int	main()
{
	int		fd;
	int		lines;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	lines = 0;
	while (lines < 3)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		lines++;
	}
	return (0);
} */
