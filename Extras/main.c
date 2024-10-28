#include "get_next_line.h"

int	main(void)
{

	int fd;
	
	fd = open("hazel.txt", O_RDWR);
	
	if (fd == -1)
	{
		perror("Error opening the file");
		return 1;
	}
	char *linereaded = NULL;
  	int n_lines = 0;
	linereaded = get_next_line(fd);
	while (linereaded != NULL)
	{
		
		n_lines++;
    	printf("%d. %s", n_lines, linereaded);
    	free(linereaded);
		linereaded = get_next_line(fd);
	}
	printf("entotal lines readed: %d\n", n_lines);
	close(fd);
    return 0;
}