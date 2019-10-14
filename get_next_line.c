
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

int    join_line(const int fd, char **line, char **segment)
{
    char        buf[BUFF_SIZE + 1];
    char        *pointer;
    int         was_read;
    char        *tmp;

    if (!line || fd < 0 || read (fd, buf, 0) < 0)
        return (-1);
    pointer = ch_segment(*segment, line);
    while (!pointer && (was_read = read(fd, buf, BUFF_SIZE)))
    {
        buf[was_read] = '\0';
        if ((pointer = ft_strchr(buf, '\n')))
        {
                *pointer = '\0';
                *segment = ft_strdup(++pointer);
        }
        tmp = *line;
        *line = ft_strjoin(*line, buf);
        free(tmp);
    }
    return (was_read ||(ft_strlen(*line))) ? 1 : 0;
}

t_gnl *add_list(const int fd)
{
    t_gnl *new;

    if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
        return (NULL);
    new->fd = fd;
    new->segment = NULL;
    new->next = NULL;
    return (new);
}

int get_next_line(const int fd, char **line)
{
    static t_gnl  *first;
    t_gnl         *tmp;

    if (first == NULL)
        first = add_list(fd);
    tmp = first;
    while (tmp->fd != fd)
    {
        if (!tmp->next)
            tmp->next = add_list(fd);
        tmp = tmp->next;
    }
    return (join_line(tmp->fd, line, &tmp->segment));
}
/*
int				main(void)
{
	char		*line1;
	char		*line2;
	char		*line3;
	int			fd1;
	int			fd2;
	int			fd3;
	int			ret1;
	int			ret2;
	int			ret3;
	char		*filename1;
	char		*filename2;
	int			errors;

	filename1 = "gnl11_1.txt";
	filename2 = "gnl11_2.txt";
	fd1 = open(filename1, O_RDONLY);
	fd2 = open(filename2, O_RDONLY);
	fd3 = -1;
	if (fd1 > 2 && fd2 > 2)
	{
		errors = 0;
		line1 = NULL;
		line2 = NULL;
		line3 = NULL;

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "The getdelim() function reads a line from stream, delimited by the character") != 0)
		{
			printf("-> must have returned '1' and read line #1 \"The getdelim() function reads a line from stream, delimited by the character\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "delimiter.  The getline() function is equivalent to getdelim() with the new-") != 0)
		{
			printf("-> must have returned '1' and read line #2 \"delimiter.  The getline() function is equivalent to getdelim() with the new-\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "line character as the delimiter.  The delimiter character is included as") != 0)
		{
			printf("-> must have returned '1' and read line #3 \"line character as the delimiter.  The delimiter character is included as\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "part of the line, unless the end of the file is reached.") != 0)
		{
			printf("-> must have returned '1' and read line #4 \"part of the line, unless the end of the file is reached.\" from file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The Festival de Radio France et Montpellier is a summer festival of opera and other music held in Montpellier.") != 0)
		{
			printf("-> must have returned '1' and read line #1 \"The Festival de Radio France et Montpellier is a summer festival of opera and other music held in Montpellier.\" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The festival concentrates on classical music and jazz with about 150 events, including opera, concerts, films, and talks. ") != 0)
		{
			printf("-> must have returned '1' and read line #2 \"The festival concentrates on classical music and jazz with about 150 events, including opera, concerts, films, and talks. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Most of these events are free and are held in the historic courtyards of the city or in the modern concert halls of Le Corum. ") != 0)
		{
			printf("-> must have returned '1' and read line #3 \"Most of these events are free and are held in the historic courtyards of the city or in the modern concert halls of Le Corum. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Le Corum cultural and conference centre contains 3 auditoriums. ") != 0)
		{
			printf("-> must have returned '1' and read line #4 \"Le Corum cultural and conference centre contains 3 auditoriums. \" from file %s\n", filename2);
			errors++;
		}

		ret3 = get_next_line(fd3, &line3);
		if (ret3 != -1)
		{
			printf("-> must have returned '-1' with invalid file descriptor\n");
			errors++;
		}
		ret1 = get_next_line(fd1, &line1);
        printf("%d\n", ret1);
        printf("%s\n", line1);
		if (ret1 != 1 || strcmp(line1, "") != 0)
		{
			printf("-> must have returned '1' and read line #5 \"\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "The caller may provide a pointer to a malloced buffer for the line in") != 0)
		{
			printf("-> must have returned '1' and read line #6 \"The caller may provide a pointer to a malloced buffer for the line in\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "*linep, and the capacity of that buffer in *linecapp.  These functions") != 0)
		{
			printf("-> must have returned '1' and read line #7 \"*linep, and the capacity of that buffer in *linecapp.  These functions\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "expand the buffer as needed, as if via realloc().  If linep points to a NULL") != 0)
		{
			printf("-> must have returned '1' and read line #8 \"expand the buffer as needed, as if via realloc().  If linep points to a NULL\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "pointer, a new buffer will be allocated.  In either case, *linep and") != 0)
		{
			printf("-> must have returned '1' and read line #9 \"pointer, a new buffer will be allocated.  In either case, *linep and\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "*linecapp will be up-dated accordingly.") != 0)
		{
			printf("-> must have returned '1' and read line #10 \"*linecapp will be up-dated accordingly.\" from file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The city is a center for cultural events since there are many students. ") != 0)
		{
			printf("-> must have returned '1' and read line #5 \"The city is a center for cultural events since there are many students. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Montpellier has two large concerts venues: Le Zenith Sud (7.000 seats) and L'Arena (14.000 seats).") != 0)
		{
			printf("-> must have returned '1' and read line #6 \"Montpellier has two large concerts venues: Le Zenith Sud (7.000 seats) and L'Arena (14.000 seats).\" from file %s\n", filename2);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 0)
		{
			printf("-> must have returned '0' at the end of file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 0)
		{
			printf("-> must have returned '0' at the end of file %s\n", filename2);
			errors++;
		}

		close(fd1);
		close(fd2);
		if (errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening files %s and/or %s\n", filename1, filename2);
	return (0);
}
*/
/*
int main(void)
{
    char *line;
    int fd;
    int fd1;
    int i = 0;

    fd = open("gnl11_1.txt", O_RDONLY);
    fd1 = open("text2.txt", O_RDONLY);
    while (get_next_line(fd, &line))
        {
            printf ("%s\n", line);
            i++;
        }
    while (get_next_line(fd1, &line) && i <= 6)
        {
            printf ("%s\n", line);
            i++;
        }
    while (get_next_line(fd, &line) && i < 9)
        {
            printf ("%s\n", line);
            i++;
        }
    return(0);
}*/