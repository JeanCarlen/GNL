/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line.h                                    :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: <auteur>                                   +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/10 12:50:00 by <auteur>          #+#    #+#             */
/* Updated: 2025/11/10 12:50:00 by <auteur>         ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *left_str, char *buff);

#endif