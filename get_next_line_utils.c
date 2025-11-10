/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_utils.c                              :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: <auteur>                                   +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/10 12:50:00 by <auteur>          #+#    #+#             */
/* Updated: 2025/11/10 12:50:00 by <auteur>         ###   ########.fr       */
/* */
/* ************************************************************************** */

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