#include "../include/cub.h"

void print_array(char **str)
{
    while (str)
    {
        printf("%s \n", str);
        str++;
    }
}

void free_array(char **str)
{
    int i;

    i = 0;
    while (str)
    {
        free(str[i]);
        i++;
    }
    free(str);
}