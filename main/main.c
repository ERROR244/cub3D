#include "../include/cub.h"

static void	fill(char const *s1, char const *s2, char *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
}

char	*fft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (s1 == NULL && s2 != NULL)
	{
		ptr = ft_strdup((char *)s2);
		free((char *)s2);
		return (ptr);
	}
	if (s2 == NULL && s1 != NULL)
	{
		ptr = ft_strdup((char *)s1);
		free((char *)s1);
		return (ptr);
	}
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	fill(s1, s2, ptr);
	free((char *)s1);
	free((char *)s2);
	return (ptr);
}



void	the_map_is_invalid(void)
{
	ft_printf("Error\n		The map is invalid\n");
	exit(EXIT_FAILURE);
}

void	invalid_file_name1(void)
{
	ft_printf("Error\n		invalid file name\n");
	exit(EXIT_FAILURE);
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
		ft_printf("Error\n		invalid file\n");
		exit(EXIT_FAILURE);
	}
	ptr = get_next_line(fd);
	if (ptr == NULL)
		the_map_is_invalid();
	str = ptr;
	str = fft_strjoin(str, NULL);
	while (ptr != NULL)
	{
		ptr = get_next_line(fd);
		str = fft_strjoin(str, ptr);
	}
	close(fd);
	sptr = fft_split((char *)str, '\n');
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
    char		**str;
	int			i;

	if (ac != 2)
		invalid_arg();
	str = name_check(av[1]);
	if (str == 0)
		the_map_is_invalid();
    print_array(str);
}