/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/28 14:44:53 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Función en cual leemos la frase del tamaño deseado :
static char	*read_phrase(int fd, char *warhouse)
{
	//Declaración de las variables :
	int		bytes_read;
	char	*buffer;
	//Reservamos la memoria en buffer de tamaño de BUFFER_SIZE más el carácter terminador.
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	//Protegemos el calloc.
	if (!buffer)
		return (NULL);
	//Inicializamos bytes_read a 1 para que tenga algo leído :
	bytes_read = 1;
	//Bucle para que lea hasta el salto de línea y que lea bytes :
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		//leemos los bytes del archivo que queremos leer :
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//Protegemos y liberamos la memoria para el caso de -1 :
		if (bytes_read == -1)
			return (free(warhouse), free(buffer), NULL);
		//Colocamos el carácter terminador al final de cada frase leída :
		buffer[bytes_read] = '\0';
		//Condición el cual si no existe warhouse, lo declaramos con una reserva de memoria de 1 :
		if (!warhouse)
			warhouse = ft_calloc(1, sizeof(char));
		//Unimos mediante un strjoin las frases que va leyendo y guardando en buffer :
		warhouse = ft_strjoin(warhouse, buffer);
		//Protegemos el malloc para leaks :
		if (!warhouse)
			return (free(buffer), NULL);
	}
	//Liberamos la memoria de buffer :
	free(buffer);
	//Retornamos warhouse :
	return (warhouse);
}
//Función que extrae la primera línea de lo leído hasta el carácter determinador :
static char	*extract_phrase(char *warhouse)
{
	//Declaración de variables :
	int		len;
	int		i;
	char	*phrase;
	
	//Inicializamos len a 0, el cual será la longitud de la cadena :
	len = 0;
	//Protegemos en el caso que warhouse no tenga nada :
	if (!warhouse[len])
		return (NULL);
	//Bucle que leerá hasta el carácter determinador :
	while (warhouse[len] && warhouse[len] != '\n')
		len++;
	//Reservamos la memoria de phrase, que será la longitud más el salto de línea y el carácter terminador :
	phrase = ft_calloc(sizeof(char), (len + 2));
	//Protegemos la reserva de memoria :
	if (!phrase)
		return (NULL);
	//Inicializamos nuestra variable que copiará desde 0 :
	i = 0;
	//Bucle que copiará desde el principio hasta el final (len) :
	while (i < len)
	{
		//Copiamos warhouse en phrase :
		phrase[i] = warhouse[i];
		i++;
	}
	//Condición el cual comprobará que el último caracter leído ser un salto de línea :
	if (warhouse[i] == '\n')
		phrase[i++] = '\n';//si lo es colocamos en la siguiente un salto de línea.
	//Por último colocamos el caracter terminador para indicar que ha acabado :
	phrase[i] = '\0';
	//Retornamos la phrase :
	return (phrase);
}
//Función que actualiza warhouse que elimina la línea leída y dejar solo el contenido restante :
static char	*clean_warhouse(char *warhouse)
{
	//Declaración de las variables :
	char	*new_warhouse;
	int		i;
	int		j;
	//Inicializamos i que será el que recorrerá lo guardado en warhouse :
	i = 0;
	//Bucle que mientras haya algo en warhouse y no sea el caracter determinador leemos:
	while (warhouse[i] && warhouse[i] != '\n')
		i++;
	//Verificamos que haya algo en warhouse y si no es así liberamos la memoria :
	if (!warhouse[i])
		return (free(warhouse), NULL);
	//Aumentamos i para que salga de ese salto de línea en el que se quedó :
	i++;
	//Reservamos la memoria de new_warhouse que contendrá los datos restantes desde la posición i más el salto de línea :
	new_warhouse = ft_calloc(sizeof(char), ft_strlen(warhouse) - i + 1);
	//Protegemos la reserva de memoria :
	if (!new_warhouse)
		return (NULL);
	//Inicializamos j copiar warhouse en new_warhouse :
	j = 0;
	//Bucle para recorrer warhouse :
	while (warhouse[i])
		//Copiamos warhouse en new_warhouse :
		new_warhouse[j++] = warhouse[i++];
	//Liberamos la memoria de warhouse :
	free(warhouse);
	//Retornamos por último new_warhouse :
	return (new_warhouse);
}
//Función principal a cual lee un archivo hasta un carácter determinado :
char	*get_next_line(int fd)
{
	//Declaración de las variables :
	char		*phrase;
	static char	*warhouse; //Nuestra variable estática.
	//Condiciones para proteger el programa de leaks :
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//A nuestra variable estática leemos la frase :
	warhouse = read_phrase(fd, warhouse);
	//Protección por si warhouse nos devuelve un NULL :
	if (!warhouse)
		return (NULL);
	//extraemos lo que hemos leído en warhouse a phrase :
	phrase = extract_phrase(warhouse);
	//Limpiamos lo warhouse, copiando el resto que quedó antes de que lo liberemos :
	warhouse = clean_warhouse(warhouse);
	//Devolvemos phrase que será el resultado final :
	return (phrase);
}
