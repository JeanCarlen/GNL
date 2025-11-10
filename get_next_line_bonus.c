/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_bonus.c                              :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: <auteur>                                   +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/10 12:50:00 by <auteur>          #+#    #+#             */
/* Updated: 2025/11/10 12:50:00 by <auteur>         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *left_str)
{
	int		i;
	char	*str;
	int		has_newline;
	int		j;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	has_newline = (left_str[i] == '\n');
	str = (char *)malloc(sizeof(char) * (i + has_newline + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i + has_newline)
	{
		str[j] = left_str[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	*newleft_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;
	size_t	len;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free (left_str);
		return (NULL);
	}
	len = ft_strlen(left_str);
	str = (char *)malloc(sizeof(char) * (len - i));
	if (!str)
	{
		free(left_str);
		return (NULL);
	}
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free (left_str);
	return (str);
}

static char	*read_and_join(int fd, char *left_str, char *buff)
{
	int	rd_bytes;

	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(left_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
		if (!left_str)
			return (NULL);
	}
	return (left_str);
}

static char	*read_str(int fd, char *left_str)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(left_str);
		return (NULL);
	}
	left_str = read_and_join(fd, left_str, buff);
	free(buff);
	if (!left_str)
		return (NULL);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*left_str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (0);
	left_str[fd] = read_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = get_line(left_str[fd]);
	left_str[fd] = newleft_str(left_str[fd]);
	return (line);
}