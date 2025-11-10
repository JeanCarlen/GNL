/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jeancarlen <jeancarlen@student.42.fr>      +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2021/11/16 11:57:46 by jcarlen           #+#    #+#             */
/* Updated: 2025/11/10 12:00:00 by jeancarlen       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
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
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
	{
		free(left_str);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (left_str[++i] != '\0')
		str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	free(left_str);
	return (str);
}

char	*get_line(char *left_str)
{
	int		i;
	int		j;
	char	*str;
	int		has_newline;

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
	while (j < i)
	{
		str[j] = left_str[j];
		j++;
	}
	if (has_newline)
	{
		str[j] = '\n';
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

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free (left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i));
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