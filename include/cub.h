/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/08/04 15:26:33 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// # include <mlx.h>
# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
    char *texture_no;
    char *texture_so;
    char *texture_we;
    char *texture_ea;
    
    char **floor_color;
    char **ceiling_color;

    char **map;
}   t_map;

// tmp
void    print_array(char **str);
void    free_array(char **str);
void    print_array_in_one_line(char **str);
// error
void	the_map_is_invalid(void);
void	invalid_file_name1(void);
void	invalid_arg(void);

char	**return_map(char *map_file);
char	**name_check(char *str);
char	*ft_strjoin3(char const *s1, char c, char const *s2);
void	the_map_is_invalid(void);
void	invalid_file_name1(void);

// map check
void	map_check(t_map *map, char **str);
void    check_texture_and_color(t_map *map, char **str);
char    **get_color(char *str, char color);

#endif