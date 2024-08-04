/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:34 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 15:23:32 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void print_array_in_one_line(char **str)
{
    int i;

    i = 0;
    printf("<:");
    while (str[i])
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
    while (str[i])
    {
        printf("%s \n", str[i]);
        i++;
    }
}

void free_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
