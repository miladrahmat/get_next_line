/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:16:00 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/05/30 15:27:26 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static int	check_fd(int fd, char **remainder)
{
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
	{
		if (remainder != NULL)
			ft_free(remainder);
		return (0);
	}
	return (1);
}

static char	*handle_remainder(char *current, char **remainder)
{
	size_t	len;
	size_t	len_nl;
	char	*result;

	result = NULL;
	len = ft_strlen(current);
	if (len == 0)
		return (ft_free(&current));
	len_nl = ft_strlen_nl(current);
	if (len != len_nl)
	{
		*remainder = ft_substr(current, len_nl + 1, len - len_nl - 1);
		if (*remainder == NULL)
			return (ft_free(&current));
		result = ft_substr(current, 0, len_nl + 1);
		if (result == NULL)
		{
			ft_free(remainder);
			return (ft_free(&current));
		}
		ft_free(&current);
	}
	if (current != NULL)
		return (current);
	return (result);
}

static char	*read_line(int fd, char *result)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	check;

	while (ft_strchr(result, '\n') == 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
			return (NULL);
		if (check == 0)
			break ;
		buffer[check] = '\0';
		temp = result;
		result = ft_strjoin(result, buffer);
		ft_free(&temp);
		if (result == NULL)
			return (NULL);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*remainder[MAX_FD];
	char			*line;

	if (check_fd(fd, &remainder[fd]) == 0)
		return (NULL);
	line = NULL;
	if (remainder[fd] != NULL)
	{
		line = ft_strjoin(line, remainder[fd]);
		ft_free(&remainder[fd]);
		if (line == NULL)
			return (NULL);
	}
	line = read_line(fd, line);
	if (line == NULL)
	{
		if (remainder[fd] != NULL)
			ft_free(&remainder[fd]);
		return (ft_free(&line));
	}
	line = handle_remainder(line, &remainder[fd]);
	return (line);
}
/* 
#include <stdio.h>
#include <fcntl.h>
int	main()
{
	int		fd;
	int		fd1;
	int		fd2;
	int		lines;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	lines = 0;
	while (lines < 7)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		line = get_next_line(fd1);
		printf("%s", line);
		free(line);
		line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		lines++;
	}
	return (0);
} */