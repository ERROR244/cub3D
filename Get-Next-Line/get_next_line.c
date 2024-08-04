/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:45:12 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 14:11:14 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		readed;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) == -1
		|| BUFFER_SIZE > 0x7fffffff)
		return (NULL);
	line = NULL;
	readed = 1;
	while (readed > 0)
	{
		if (buf[0] == 0)
			readed = read(fd, buf, BUFFER_SIZE);
		if (readed > 0)
			line = my_line(line, buf);
		if (is_it_nline(buf))
			break ;
	}
	return (line);
}

// int main()
// {
//     int fd = open("test.txt", O_RDONLY);
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
