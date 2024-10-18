#include "get_next_line.h"

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
    // // Leemos línea por línea con get_next_line
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