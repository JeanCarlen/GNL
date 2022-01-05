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

char	*get_buffer(int fd, char *overflow)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(overflow, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes < 0)
		{
			free (buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		overflow = ft_strjoin(overflow, buff);
	}
	free (buff);
	return (overflow);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*overflow;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	overflow = get_buffer(fd, overflow);
	if (!overflow)
		return (NULL);
	line = get_n_cut(overflow);
	overflow = ow_in_newstr(overflow);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 11)
	{
		line = get_next_line(fd1);
		printf("\n line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("\n line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/