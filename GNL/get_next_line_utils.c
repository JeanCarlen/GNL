/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarlen <jcarlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:46 by jcarlen           #+#    #+#             */
/*   Updated: 2022/02/04 13:33:33 by jcarlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(s1) + ft_strlen(buff)] = '\0';
	free(s1);
	return (str);
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
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

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

char	*get_n_cut(char *overflow)
{
	int		i;
	char	*line;

	i = 0;
	if (!overflow[i])
		return (NULL);
	while (overflow[i] && overflow[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (overflow[i] && overflow[i] != '\n')
	{
		line[i] = overflow[i];
		i++;
	}
	if (overflow[i] == '\n')
	{
		line[i] = overflow[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ow_in_newstr(char *overflow)
{
	int		i;
	int		j;
	char	*new_ow;

	i = 0;
	while (overflow[i] && overflow[i] != '\n')
		i++;
	if (!overflow[i])
	{
		free (overflow);
		return (NULL);
	}
	new_ow = (char *)malloc(sizeof(char) * (ft_strlen(overflow) - i + 1));
	if (!new_ow)
		return (NULL);
	i++;
	j = 0;
	while (overflow[i])
		new_ow[j++] = overflow[i++];
	new_ow[j] = '\0';
	free (overflow);
	return (new_ow);
}
