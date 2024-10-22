/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/18 11:44:11 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_phrase(int fd, char *warhouse)
{
	int		bytes_read;
	char	*buffer;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(warhouse, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(warhouse), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		warhouse = ft_strjoin(warhouse, buffer);
		if (!warhouse)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (warhouse);
}

static char	*extract_phrase(char *warhouse)
{
	int		len;
	char	*phrase;

	len = 0;
	if(!warhouse[len])
		return (NULL);
	while (warhouse && warhouse[len] != '\n')
		len++;
	phrase = ft_calloc(sizeof(char), (len + 2)); //Contando salto de linea y el caracter terminador.
	if (!phrase)
		return (NULL);
	len = 0;
	if(warhouse && warhouse[len] == '\n')
	{
		phrase[len] = warhouse[len];
		len++;
	}
	return (phrase);
}


static char	*clean_warhouse(char *warhouse)
{
	char	*new_rest;
	int		i;
	int		j;

	i = 0;
	while (warhouse[i] && warhouse[i] != '\n')
		i++;
	if (!warhouse[i])
	{
		free (warhouse);
		return (NULL);
	}
	new_rest =(char *)ft_calloc(sizeof(char), ft_strlen(warhouse) - i + 1);
	if (!new_rest)
		return (NULL);
	i++;
	j = 0;
	while (warhouse[i])
		new_rest[j++] = warhouse[i++];
	free(warhouse);
	return (new_rest);
}

char	*get_next_line(int fd)
{
	char		*line_readed;
	static char	*warhouse;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	warhouse = read_phrase(fd, warhouse);
	printf("hola");
	if (!warhouse)
		return (NULL);
	line_readed = extract_phrase(warhouse);
	warhouse = clean_warhouse(warhouse);
	return (line_readed);
}

int	main(void)
{
	int fd = open("el_quijote.txt", O_RDONLY); 
	if (fd == -1)
	{
		perror("Error opening the file");
		return 1;
	}
	char *linereaded = NULL;
  	int n_lines = 0;
	while ((linereaded = get_next_line(fd)) != NULL)
	{
		n_lines++;
    	printf("%d. %s", n_lines, linereaded);
    	free(linereaded);
	}
	printf("\ntotal lines readed: %d\n", n_lines);
	close(fd);
    return 0;
}
