
#include "get_next_line.h"

char    *ch_segment(char *segment, char **line)
{
    char    *pointer;

    pointer = NULL;
    if (segment)
        if ((pointer = ft_strchr(segment, '\n')))
        {
            *pointer = '\0';
            *line = ft_strdup(segment);
            ft_strcpy(segment, ++pointer);
        }
        else
        {
            *line = ft_strdup(segment);
            ft_strclr(segment);
        }
    else
        *line = ft_strnew(1);
    return (pointer);
}

 int    get_next_line(const int fd, char **line)
{
    char        buf[BUFF_SIZE + 1];
    char        *pointer;
    int         was_read;
    static char *segment;
    char        *tmp;

    if (!line || fd < 0 || read (fd, buf, 0) < 0)
        return( -1);
    pointer = ch_segment(segment, line);
    while (!pointer && (was_read = read(fd, buf, BUFF_SIZE)))
    {
        buf[was_read] = '\0';
        if ((pointer = ft_strchr(buf, '\n')))
        {
                *pointer = '\0';
                segment = ft_strdup(++pointer);
        }
        tmp = *line;
        *line = ft_strjoin(*line, buf);
        free(tmp);
    }
    return (was_read || ft_strlen(*line)) ? 1 : 0;
}

/*int main(void)
{
    char *line;
    int fd;
    fd = open("text.txt", O_RDONLY);
    while (get_next_line(fd, &line))
        printf ("%s\n", line);
    return(0);
}
*/