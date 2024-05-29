/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:02:55 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/05/29 15:20:19 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*ptr;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		else
			i++;
	}
	if (s[i] == (char)c)
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	else
		return (0);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	unsigned int	s1_i;
	unsigned int	s2_i;
	unsigned int	new_i;
	char			*new;

	if (s1 == NULL)
		s1 = "";
	s1_i = 0;
	s2_i = 0;
	new_i = 0;
	while (s1[s1_i] != '\0')
		s1_i++;
	while (s2[s2_i] != '\0')
		s2_i++;
	new = (char *)malloc((s1_i + s2_i) * sizeof(char) + 1);
	if (new == 0)
		return (0);
	s1_i = 0;
	s2_i = 0;
	while (s1[s1_i] != '\0')
		new[new_i++] = s1[s1_i++];
	while (s2[s2_i] != '\0')
		new[new_i++] = s2[s2_i++];
	new[new_i] = '\0';
	return (new);
}

size_t	ft_strlen_nl(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\n' && str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
