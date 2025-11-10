/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_bonus.h                              :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jeancarlen <jeancarlen@student.42.fr>      +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2021/11/16 11:57:56 by jcarlen           #+#    #+#             */
/* Updated: 2025/11/10 12:00:00 by jeancarlen       ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *left_str, char *buff);
char	*get_line(char *left_str);
char	*newleft_str(char *left_str);
char	*read_str(int fd, char *left_str);

#endif