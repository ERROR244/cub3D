/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:45:12 by ksohail-          #+#    #+#             */
/*   Updated: 2023/12/10 21:01:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
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
///int main() {
   //  int fd = open("test.txt", O_RDONLY);
//     if (fd == -1) {
 //        perror("open");
   //      return (1);
    // }

//   char *ptr;
 //	ptr = get_next_line(fd);
   //   while ((ptr = get_next_line(fd)) != NULL) {
     //    printf("%s", ptr);
       //  free(ptr);
//      }
  //    printf("\ndone \n");
    //  printf("%s \n", ptr);
 //	 system("leaks a.out");
   //  close(fd);
 //}
