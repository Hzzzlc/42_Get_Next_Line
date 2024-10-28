#include "get_next_line.h"

static char	*read_phrase(int fd, char *warhouse)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(warhouse, '\n'))
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
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	*extract_phrase(char *warhouse)
{
	int		len;
	char	*pointer;
	char	*phrase;

	pointer = ft_strchr(warhouse, '\n');
	if (!pointer)
		return (NULL);
	len = (pointer - warhouse) + 1;
	phrase = ft_substr(warhouse, 0, len);
	if (!phrase)
		return (NULL);
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


char	*get_next_line(int fd)
{
	char		*phrase;
	static char	*warhouse;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (warhouse == NULL)
		warhouse = ft_strdup("");
	if (!warhouse)
		return (NULL);
	warhouse = read_phrase(fd, warhouse);
	if (!warhouse)
		return (NULL);
	phrase = extract_phrase(warhouse);
	if (!phrase)
		return (ft_free(&warhouse));
	warhouse = clean_warhouse(warhouse);
	return (phrase);
}

int main(void)
{
    int     fd;
    char    *line;

    fd = open("hazel.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }
	line = get_next_line(fd);
	int n_lines = 1;

    while (line != NULL && n_lines < 10)
    {
        free(line);   
		line = get_next_line(fd);
		n_lines++;
    }
	printf("%s", line);
	close(fd);
    return (0);
}