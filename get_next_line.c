/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/16 16:21:44 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **phrase);
static char	*clean_warhouse(char *warhouse);
static char	*extract_phrase(char *warhouse);
static char	*read_phrase(int fd, char *warhouse);

char	*get_next_line(int fd)
{
	char		*phrase;
	static char	*warhouse;
    
	if (!fd)
		return (NULL);
	warhouse = read_phrase(fd, warhouse);
	phrase = extract_phrase(warhouse);
	if (!phrase)
		return (ft_free(&warhouse));
	warhouse = clean_warhouse(warhouse);
	return (phrase);
}

static char	*read_phrase(int fd, char *warhouse)
{

	int		bytes_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&warhouse));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(warhouse, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(warhouse), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		warhouse = ft_strjoin(warhouse, buffer);
		if (!warhouse)
			return(free(buffer), NULL);
	}
	free(buffer);
	return (warhouse);
}

static char	*extract_phrase(char *warhouse)
{
	int		len;
	char	*pointer;
	char	*phrase;

 	pointer = ft_strchr(warhouse, '\n');
	len = (pointer - warhouse) + 1;
	phrase = ft_substr(warhouse, 0, len);
	if (!phrase)
		return(NULL);
	return (phrase);
}

static char	*ft_free(char **phrase)
{
	free(*phrase);
	*phrase = NULL;
	return (NULL);
}

static char	*clean_warhouse(char *warhouse)
{
	int		len;
	char	*pointer;
	char	*new_warhouse;
    
	pointer = ft_strchr(warhouse, '\n');
	if (!pointer)
	{
		new_warhouse = NULL;
		return (ft_free(&warhouse));
	}
	else
		len = (pointer - warhouse) + 1;
	new_warhouse = ft_substr(warhouse, len, ft_strlen(warhouse) - len);
	ft_free(&warhouse);
	if (!new_warhouse)
		return (NULL);
	return (new_warhouse);
}

int main(void)
{
    int     fd;
    char    *line;

    // Abrimos el archivo que queremos leer
    fd = open("hazel.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }
	else if(fd == 0)
		perror("No ha leido el archivo.");
    // Leemos línea por línea con get_next_line
	line = get_next_line(fd);
	int n_lines = 1;
    while (line != NULL && n_lines < 10)
    {
        printf("%d. %s", n_lines, line); // Imprimimos la línea
        free(line);   
		line = get_next_line(fd);
		n_lines++;      // Liberamos la memoria asignada para la línea
    }
	printf("%s", line);
	close(fd);
    return (0);
}
//gestionar el ultimo salto de linea ya que libera la statica perdiendo lo que habia.
