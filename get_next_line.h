/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:50:49 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/09 15:34:14 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFERSIZE 20

#if BUFFERSIZE >= 10000000 || BUFFERSIZE < 1
    #undef BUFFERSIZE
    #define BUFFERSIZE 256
#endif

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
#endif
