#include "get_next_line.h"


char *GNL()
{
	//Declaracion de variables :
	int fd;
	int bytes_read;
	char *buffer;
	char *cadenas;

	//Inicializamos bytes_read a 1 porque se debe inicializar para el read :
	bytes_read = 1;
	//Abrimos el archivo .txt :
	fd = open("hazel.txt", O_RDWR);
	//Reservamos memoria :
	buffer = malloc(sizeof(char) * (BUFFERSIZE + 1));
	//Protegemos el malloc :
	if(!buffer)
		return NULL;
	//Reservamos memoria para cadenas :
	// cadenas = malloc(1);
	//Protegemos el malloc :
	// if(!cadenas)
	// 	return 0;
	while(bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFERSIZE);
		//poner el caracter terminador :
		buffer[bytes_read] = '\0';
		char *position = ft_strchr(buffer, '.');
		//Si comentamos esta funcion me imprime todo.
		if(position != NULL)
		{
			//le ponemos el caracter nulo al final de la cadena :
			*position = '\0';
			//Concatenamos lo que ha guardado en una cadena sola hasta el punto :
			cadenas = ft_strjoin(cadenas, buffer);
			//Guardamos tambien lo que encuentra hasta el caracter determinador :
			cadenas = ft_strjoin(cadenas, ".");
			//Cuando se cumple esto salimos de bucle :
			break;
		}
		//Concatenamos todo el contenido leido que se gaurdo.:
		cadenas = ft_strjoin(cadenas, buffer);

	}
	//liberamos buffer :
	free(buffer);
	//Retornamos cadenas donde se almacena todo :
	return cadenas;
}
static char *extract_phrase(char *cadenas)
{
	//Declaracion de variables :
	int len; //La longitud de hasta donde se va a extaer esa frase.
	char *phrase; //La frase extraida.
	char *pointer;//Puntero donde de indicamos hasta donde queremos que nos lea.

	//Le indicamos que solo queremos hasta el salto de linea.
	pointer = ft_strchr(cadenas, '\n');
	//Calculamos la longitud de la frase incluyendo el caracter terminador.
	len = (pointer - cadenas) + 1;
	//Sacamos la frase que queremos.
	phrase = ft_substr(cadenas, 0, len);
	//Como substr utiliza malloc, protegemos el malloc.
	if(!phrase)
	 return (NULL);
	//Retornamos la frase.
	return (phrase);
}
char	*ft_strjoin(const char *s1, const char *s2)
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
	return (new_s);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

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
int main ()
{
	char *paragraph = GNL();

	if (paragraph != NULL) {
		printf("First paragraph:\n%s\n", paragraph);
	free(paragraph);
	} else {
	printf("Error reading the file or empty file.\n");
	}

	return 0;
}
