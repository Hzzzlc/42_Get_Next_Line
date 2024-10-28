/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/28 12:35:56 by hcruz-me         ###   ########.fr       */
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
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return(free(warhouse), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		if (!warhouse)
			warhouse = ft_calloc(1, sizeof(char)); 
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
	int		i;
	char	*phrase;

	len = 0;
	if(!warhouse[len])
		return (NULL);
	while (warhouse[len] && warhouse[len] != '\n')
		len++;
	phrase = ft_calloc(sizeof(char), (len + 2));
	if (!phrase)
		return (NULL);
	i = 0;
	while (i < len)
	{
		phrase[i] = warhouse[i];
		i++;
	}
	if (warhouse[i] == '\n')
		phrase[i++] = '\n';
	phrase[i] = '\0';
	return (phrase);
}


static char	*clean_warhouse(char *warhouse)
{
	char	*new_warhouse;
	int		i;
	int		j;

	i = 0;
	while (warhouse[i] && warhouse[i] != '\n')
		i++;
	if (!warhouse[i])
		return(free(warhouse), NULL);
	i++;
	new_warhouse = ft_calloc(sizeof(char), ft_strlen(warhouse) - i + 1);
	if (!new_warhouse)
		return (NULL);
	j = 0;
	while (warhouse[i])
		new_warhouse[j++] = warhouse[i++];
	free(warhouse);
	return (new_warhouse);
}

char	*get_next_line(int fd)
{
	char		*phrase;
	static char	*warhouse;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	warhouse = read_phrase(fd, warhouse);
	if (!warhouse)
		return (NULL);
	phrase = extract_phrase(warhouse);
	warhouse = clean_warhouse(warhouse);
	return (phrase);
}

// int	main(void)
// {

// 	int fd;
	
// 	fd = open("hazel.txt", O_RDWR);
	
// 	if (fd == -1)
// 	{
// 		perror("Error opening the file");
// 		return 1;
// 	}
// 	char *linereaded = NULL;
//   	int n_lines = 0;
// 	linereaded = get_next_line(fd);
// 	while (linereaded != NULL)
// 	{
		
// 		n_lines++;
//     	printf("%d. %s", n_lines, linereaded);
//     	free(linereaded);
// 		linereaded = get_next_line(fd);
// 	}
// 	printf("entotal lines readed: %d\n", n_lines);
// 	close(fd);
//     return 0;
// }
