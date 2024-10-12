/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcruz-me <hcruz-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:51 by hcruz-me          #+#    #+#             */
/*   Updated: 2024/10/10 16:39:50 by hcruz-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
	Pasos para empezar GNL:
	- La funcion de este proyecto es que te lea mediante un tamano definido en buffersize y te lo imprima tal cual el archivo
	  con sus saltos de linea, sus espacios, etc.
	- Saber abrir y cerrar el archivo .txt. == HECHO
	- Imprimir el pimer parrafo, es decir hasta el primer salto de linea que encuentra.
	- Va a leer de 20 en 20 caracteres y cuando termine de leer los primeros 20 va a poner +1 para el caracter nulo
	  cuando vuelva a leer los otros 20 caracteres que tambien le pone el caracter nulo, hacemos un strjoin para unirlas.
	- Malloc sera sizeof * nuestro buffersize + 1 para luego en el while cuando se copia toda la cadena en el ultimo caracter
	  le ponemos buffer[bytes_read] = '\0'.
	- Vamos a tener la variable bytes_read, que va a ser los bytes leidos que luego se almacenaran en buffer.
	- RECUERDA : liberar siempre cada malloc, STRJOIN contiene malloc asi que despues de utlizarlo debes liberar.
	- La variable estatica funciona para guardar donde se quedo al pedir que imprima desde un punto a otro.
	- Si termina de leer en un punto donde hay un salto de linea este debe estar incluido tambien el nulo a parte del salto de linea
	- READ  sera para leer tenemos nuestro fd, nuestro buffer y nuestro tamano.
	- LAS FUNCIONES A UTILIZAR LAS TENEMOS EN : get_next_line_utils.c y en su libreria.
	- RECUERDA proteger mejor nuestras funciones ya utilizadas en la Libft, tienen que estar mejor realizadas para el tema de leaks.
*/
char	*get_next_line(int fd)
{
	fd = open("hazel.txt", O_RDWR);
}
char *set_line(char *buffer)
{
	int fd;
	ssize_t bytes_read;
	fd = open("hazel.txt", O_RDONLY);
	int commit;
	//Hay que leer el archivo hasta que encuentre un
	//un salgo de linea esto se hara con strchr.
	//esto a su vez generara un buffer que sea del tamano
	//de lo que ha leido.
}
//Tendremos otra funcion que rellenara el buffer a la linea
//que copio, la cual se le pasara como parametro fd, char lesftc
//char buffer. utilizaremos tambien BUFFER_SIZE, hasta el salto de
//linea o terminador.
