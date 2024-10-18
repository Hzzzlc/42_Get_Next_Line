/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:50:21 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/18 11:26:11 by hcruz-me         ###   ########.fr       */
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*new_s;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (s + start), len + 1);
	return (substr);
}
