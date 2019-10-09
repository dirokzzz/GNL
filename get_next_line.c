#include <stdio.h>
#include "libft.h"
#include "ft_strdup.c"
#include "ft_strnew.c"
#include "ft_strlen.c"
#include "ft_strjoin.c"
#include "ft_strlcat.c"
#include "ft_strchr.c"
#include <fcntl.h>
# define BUFF_SIZE 10000

 int get_next_line(const int fd, char **line)
{
    char buf[BUFF_SIZE + 1];
    char *pointer;
    int was_read;
    static char *segment;

    if (segment)
        *line = ft_strdup(segment);
    else
        *line = ft_strnew(1);
    while ((was_read = read(fd, buf, BUFF_SIZE)))
    {
        buf[was_read] = '\0';
        if ((*pointer = *ft_strchr(buf, '\n')))
        {
                *pointer = '\0';
                *line = ft_strjoin(*line, buf);
                segment = ft_strdup (++pointer);
                break;
        }
        *line = ft_strjoin(*line, buf);
    }
    return (0);
}

int main()
{
    char *line;
    int fd;
    fd = open("text.txt", O_RDONLY);
    get_next_line(fd, &line);
    printf ("%s\n", line);
    get_next_line(fd, &line);
    printf ("%s\n", line);
    get_next_line(fd, &line);
    printf ("%s\n", line);
    get_next_line(fd, &line);
    printf ("%s\n", line);
    get_next_line(fd, &line);
    printf ("%s\n", line);
    return(0);
}