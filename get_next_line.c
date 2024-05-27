/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:14 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/05/27 17:38:12 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *result)
{
	char	*buffer;
	char	*nl_ptr;
	ssize_t	check;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	nl_ptr = 0;
	while (nl_ptr == 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (check == 0)
			break ;
		buffer[check] = '\0';
		nl_ptr = ft_strchr(buffer, '\n');
		result = ft_strjoin(result, buffer);
		if (result == NULL)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*line;
	size_t			len;
	size_t			len_nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(1 * sizeof(char));
	if (line == NULL)
		return (NULL);
	*line = '\0';
	if (remainder != NULL)
	{
		line = ft_strjoin(line, remainder);
		free(remainder);
		remainder = NULL;
		if (line == NULL)
			return (NULL);
	}
	line = read_line(fd, line);
	len = ft_strlen(line);
	len_nl = ft_strlen_nl(line);
	if (len != len_nl)
	{
		remainder = ft_substr(line, len_nl + 1, len - len_nl - 1);
		if (remainder == NULL)
		{
			free(line);
			return (NULL);
		}
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
	while (lines < 1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		lines++;
	}
	return (0);
} */
