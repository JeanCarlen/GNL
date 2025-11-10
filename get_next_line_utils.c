#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

/*
** Helper pour ft_strjoin : copie les deux chaînes dans la nouvelle.
*/
static void	ft_perform_copy(char *str, char *left_str, char *buff)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (left_str[++i] != '\0')
		str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
}

char	*ft_strjoin(char *left_str, char *buff)
{
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		if (!left_str)
			return (NULL);
		left_str[0] = '\0';
	}
	if (!buff)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(left_str) + ft_strlen(buff) + 1));
	if (str == NULL)
	{
		free(left_str);
		return (NULL);
	}
	ft_perform_copy(str, left_str, buff);
	free(left_str);
	return (str);
}

char	*get_line(char *left_str)
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

char	*newleft_str(char *left_str)
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