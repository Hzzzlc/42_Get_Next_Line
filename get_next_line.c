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

char	*get_next_line(int fd)
{
	fd = open("hazel.txt", O_RDWR);
}
char *set_line(char *buffer)
{
	int fd;
	ssize_t bytes_read;
	fd = open("hazel.txt", O_RDONLY);
	//Hay que leer el archivo hasta que encuentre un
	//un salgo de linea esto se hara con strchr.
	//esto a su vez generara un buffer que sea del tamano
	//de lo que ha leido.
}
//Tendremos otra funcion que rellenara el buffer a la linea
//que copio, la cual se le pasara como parametro fd, char lesftc
//char buffer. utilizaremos tambien BUFFER_SIZE, hasta el salto de
//linea o terminador.
