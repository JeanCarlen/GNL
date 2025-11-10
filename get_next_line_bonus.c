#include "get_next_line_bonus.h"


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

char	*read_str(int fd, char *left_str)
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