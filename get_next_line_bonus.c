/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:49 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/28 15:11:36 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Funcion que leera la frase del tamano deseado determinado en BUFFERSIZE :
static char	*read_phrase(int fd, char *warhouse)
{
	//Declaracion de variables :
	int		bytes_read;
	char	*buffer;
	//Reserva de memoria donde se guardara lo leido mas el caracter terminador :
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	//Protegemos el malloc :
	if (!buffer)
		return (NULL);
	//Inicializamos bytes a lago leido aunque sea un 1 caracter :
	bytes_read = 1;
	//Bucle que leera cuando bytes sea distinto de cero y hasta el salto de linea :
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		//leemos el archivo hasta el tamano de BUFFERSIZE :
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//En caso de que bytes sea -1 liberamos memoria y devolvemos NULL :
		if (bytes_read == -1)
			return (free(warhouse), free(buffer), NULL);
		//Colocamos el caracter terminador al final de la frase leida :
		buffer[bytes_read] = '\0';
		//Condicion el cual si warhouse no existe, lo declaramos con una reserva de memoria de 1.
		if (!warhouse)
			warhouse = ft_calloc(1, sizeof(char));
		//Unimos mediante strjoin lo que se va leyendo y guardando en warhouse :
		warhouse = ft_strjoin(warhouse, buffer);
		//Protegemos el strjoin para posibles leaks :
		if (!warhouse)
			return (free(buffer), NULL);
	}
	//Liberamos la memoria de buffer :
	free(buffer);
	//Retirnamos warhouse :
	return (warhouse);
}
//Funcion para extraer la primera linea leida hasta el caracter determinador :
static char	*extract_phrase(char *warhouse)
{
	//Declaracion de variables :
	int		len;
	int		i;
	char	*phrase;

	//Inicializamos len a 0 :
	len = 0;
	//Protegemos nuestro programa :
	if (!warhouse[len])
		return (NULL);
	//Leemos cuando exista algo en warhouse y no sea un salto de linea :
	while (warhouse[len] && warhouse[len] != '\n')
		len++;
	//Reservamos memoria en phrase que sera lo leido mas el salto de linea y el caracter terminador :
	phrase = ft_calloc(sizeof(char), (len + 2));
	//Protegemos el malloc :
	if (!phrase)
		return (NULL);
	//Inicializamos la variable i que recorrera desde el primer caracter hasta el ultimo :
	i = 0;
	//Mientras no sea el final de la frase :
	while (i < len)
	{
		//Copiamos warhouse en phrase :
		phrase[i] = warhouse[i];
		i++;
	}
	//Comprobacion de ver si el ultimo caracter leido es un salto de linea :
	if (warhouse[i] == '\n')
		phrase[i++] = '\n';//Si es asi colocamos en el siguiente un salto de linea.
	//Por ultimo colocamos el caracter terminador :
	phrase[i] = '\0';
	//Retornamos phrase :
	return (phrase);
}
//Funcion que actualiza warhouse, elimina la linea leida y deja solo el contenido restante :
static char	*clean_warhouse(char *warhouse)
{
	//Declaracion de las variables :
	char	*new_warhouse;
	int		i;
	int		j;
	//Inicializamos i que sera el que recorrera lo guardado en warhouse :
	i = 0;
	//Mientras exista warhouse y no sea un salto de linea :
	while (warhouse[i] && warhouse[i] != '\n')
		i++;
	//Si warhouse no existe liberamos memoria :
	if (!warhouse[i])
		return (free(warhouse), NULL);
	//Aunmentamos i para saltar el salto de linea en el que nos quedamos :
	i++;
	//Reservamos memoria de new_warhouse el cual contendra los datos restantes desde la posicion i mas el salto de linea :
	new_warhouse = ft_calloc(sizeof(char), ft_strlen(warhouse) - i + 1);
	//Protegemos el malloc :
	if (!new_warhouse)
		return (NULL);
	//Inicializamos j que sera el que recorrera todas las posiciones de new_warhouse :
	j = 0;
	//Bucle que mientras exista warhouse copiamos warhouse en new_warhouse :
	while (warhouse[i])
		new_warhouse[j++] = warhouse[i++];
	//Liberamos la memoria de warhouse :
	free(warhouse);
	//Retornamos new_warhouse :
	return (new_warhouse);
}

char	*get_next_line(int fd)
{
	//Declaracion de varaibles :
	char		*phrase;//almacenara la linea leida completa antes de devolverla.
	static char	*warhouse[MAXBUFF];//variable donde se almacenara lo que no se ha leido completamente. archivos a poder abrir 1024.

	//Condiciones para proteger el programa de leaks :
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//lo que cambia es que warhouse es en posicion fd para que guarde lo que ha leido de un fd en concreto.
	warhouse[fd] = read_phrase(fd, warhouse[fd]);
	//Protegemos el warhouse.
	if (!warhouse[fd])
		return (NULL);
	phrase = extract_phrase(warhouse[fd]);
	warhouse[fd] = clean_warhouse(warhouse[fd]);
	return (phrase);
}
