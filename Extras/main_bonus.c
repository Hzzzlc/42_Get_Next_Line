#include "get_next_line_bonus.h"

int main()
{
    int fd1;
    int fd2;
    char *line1;
    char *line2;

    fd1 = open("hazel.txt", O_RDONLY);
    fd2 = open("el_quijote.txt", O_RDONLY);
    while(1)
    {
        line1 = get_next_line(fd1);
        if(line1)
        {
            printf("Archivo 1 : %s", line1);
            free(line1);
        }
        line2 = get_next_line(fd2);
        if(line1)
        {
            printf("Archivo 2 : %s", line2);
            free(line2);
        }
        if(!line1 && !line2)
            break;
    }
    close(fd1);
    close(fd2);
    return 0;
}