/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarlen <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:30 by jcarlen           #+#    #+#             */
/*   Updated: 2021/11/16 11:57:34 by jcarlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd);

char	*ft_strdup(char *src);

char	*read_str(int fd, char *left_str);

char	*read_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFF_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFF_SIZE);
		if (rd_bytes == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free (buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*left_str;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (0);
	left_str = read_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = get_line(left_str);
	left_str = newleft_str(left_str);
	return (line);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (copy == 0)
		return (0);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int main()
{
	char	*line;
	int		i;
	int		fd;

	fd = open("hello.txt", O_RDNLY);
	i = 1;
	while (1 < 7)
	{
		line = get_next_line(fd);
		printf("line [%02d]: %s", i, line);
		free (line);
		i++;
	}
	close (fd);
	return (0);
}