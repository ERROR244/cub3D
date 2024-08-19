/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:45:12 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/05 10:06:02 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strjoin_gcl(char *remains, char *buffer)
{
    char *array;
    unsigned int size;
    int i;
    int j;

    if (!remains && !buffer)
        return (NULL);
    size = ft_strlen(remains) + ft_strlen(buffer);
    if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
        return (NULL);
    i = 0;
    j = 0;
    if (remains)
    {
        while (remains[i])
            array[j++] = remains[i++];
        i = 0;
    }
    while (buffer[i])
        array[j++] = buffer[i++];
    array[size] = '\0';
    free((void *)remains);
    return (array);
}

char     *get_next_line(int fd)
{
    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    char buffer[BUFFER_SIZE + 1];
    buffer[0] = '\0';
    static char *remains;
	char *line;
    int count;

    count = 1;
    while (!find_new_line(buffer) && count != 0)
    {
        if ((count = read(fd, buffer, BUFFER_SIZE)) == (-1))
            return (NULL);
        buffer[count] = '\0';
        remains = ft_strjoin_gcl(remains, buffer);
    }
    line = push_line(remains);
    remains = cut_next_line(remains);
	if (line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    return (line);
}

// int main()
// {
//     int fd = open("../file.cub", O_RDONLY);
//     if (fd == -1)
// 	{
//         perror("open");
//         return (1);
//     }

// 	char *ptr;
//     while ((ptr = get_next_line(fd)) != NULL)
// 	{
//        printf(":%s:\n", ptr);
//        free(ptr);
//     }
//  	system("leaks a.out");
//     close(fd);
// }
