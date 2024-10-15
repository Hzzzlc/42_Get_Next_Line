/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/14 12:58:53 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_phrase(int fd, char *warhouse)
{
    int bytes_read;
    char *buffer;
    char *position;

    bytes_read = 1;
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        buffer[bytes_read] = '\0';
        position = ft_strchr(buffer, '\n');
        if (position != NULL)
        {
            *position = '\0';
            warhouse = ft_strjoin(warhouse, buffer);
            warhouse = ft_strjoin(warhouse, ".");
            break;
        }
        warhouse = ft_strjoin(warhouse, buffer);
    }
    if(bytes_read < 0)
        return (NULL);
    return (warhouse);
}

static char *extract_phrase(char *warhouse)
{
    char *pointer;
    int len;
    char *phrase;

    pointer = ft_strchr(warhouse, '\n');
    len = (pointer - warhouse) + 1;
    phrase = ft_substr(warhouse, 0, len);
    return (phrase);
}

char *get_next_line(int fd)
{
    static char warhouse;
    char *phrase;

    warhouse = 0;
    if (!fd)
        return (NULL);
    if (warhouse && !ft_strchr(warhouse, '\n'))
        warhouse = read_phrase(fd, warhouse);
    phrase = extract_phrase(warhouse);
}
int main ()
{
	char *paragraph = get_next_line();
		printf("First paragraph:\n%s\n", paragraph);
	return 0;
}