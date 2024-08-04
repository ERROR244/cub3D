/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/08/04 12:25:37 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
// # include <mlx.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

void print_array(char **str);
//
static void	fill(char const *s1, char const *s2, char *ptr);
char	*fft_strjoin(char const *s1, char const *s2);
//
void	the_map_is_invalid(void);
void	invalid_file_name1(void);
char	**return_map(char *map_file);
char	**name_check(char *str);
#endif