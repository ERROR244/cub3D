#include "../include/cub.h"

void print_array(char **str)
{
    while (str)
    {
        printf("%s \n", str);
        str++;
    }
}