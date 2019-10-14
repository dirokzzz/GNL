#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_gnl
{
    int     fd;
    char    *segment;
    struct  s_gnl *next;
}              t_gnl;

#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>
# define BUFF_SIZE 32

#endif