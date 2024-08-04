/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:34 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 16:54:44 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void print_array_in_one_line(char **str)
{
    int i;

    i = 0;
    printf("<:");
    while (str && *str && str[i])
    {
        printf("%s:", str[i]);
        i++;
    }
    printf(">\n");
}

void print_array(char **str)
{
    int i;

    i = 0;
    while (str && *str && str[i])
    {
        printf("%s \n", str[i]);
        i++;
    }
}

void print_array_of_int(int *color)
{
    int i;

    i = 0;
    printf("<:");
    while (color && *color && i < 3)
    {
        printf("%d:", color[i]);
        i++;
    }
    printf(">\n");
}

void free_array(char **str)
{
    int i;

    i = 0;
    while (str && *str && str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
