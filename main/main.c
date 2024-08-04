/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 14:54:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*ft_strjoin3(char const *s1, char c, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL && s2 != NULL)
		return ((char *)s2);
	if (s2 == NULL && s1 != NULL)
		return ((char *)s1);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
    free((char *)s1);
    free((char *)s2);
	return (ptr);
}

char	**return_map(char *map_file)
{
	char	*ptr;
	char	*str;
	int		fd;
	char	**sptr;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n		invalid file\n");
		exit(EXIT_FAILURE);
	}
	ptr = get_next_line(fd);
	if (ptr == NULL)
    {        
		the_map_is_invalid();
    }
	str = ptr;
	while (ptr != NULL)
	{
		ptr = get_next_line(fd);
		str = ft_strjoin3(str, '\n', ptr);
	}
	close(fd);
	sptr = ft_split(str, '\n');
	free(str);
	return (sptr);
}

char	**name_check(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i--] != 'b')
		invalid_file_name1();
	if (str[i--] != 'u')
		invalid_file_name1();
	if (str[i--] != 'c')
		invalid_file_name1();
	if (str[i--] != '.')
		invalid_file_name1();
	return (return_map(str));
}

int main(int ac, char **av)
{
    t_map       map;
    char		**str;

	if (ac != 2)
		invalid_arg();
	str = name_check(av[1]);
	if (str == 0)
    {
		the_map_is_invalid();
    }
    print_array(str);
    free_array(str);
}
