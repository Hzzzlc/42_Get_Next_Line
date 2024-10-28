/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:50:21 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/24 15:10:14 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*sptr;

	sptr = (char *)s;
	count = 0;
	while (sptr[count] != '\0')
	{
		if ((char)sptr[count] == (char)c)
			return (&sptr[count]);
		count++;
	}
	if ((char)c == '\0')
		return (&sptr[count]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*copia;
	int		count;
	int		i;

	count = ft_strlen(s);
	copia = malloc((count + 1) * sizeof(char));
	if (!copia)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copia[i] = s[i];
		i++;
	}
	copia[i] = '\0';
	return (copia);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		len;
	int			i;
	int			j;
	char		*new_s;

	// if (!s1)
	//  	s1 = malloc(1);
	if (!s1 || !s2)
	 	return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = ft_calloc((len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	i = -1;
	while (s1[++i])
		new_s[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	return (new_s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	total_size;
	size_t	i;
	unsigned char	*ptr;

	total_size = nmemb * size;
	buffer = malloc(total_size);
	if (!buffer)
		return (NULL);
	ptr = (unsigned char *)buffer;
	i = 0;
	while (i < total_size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (buffer);
}
