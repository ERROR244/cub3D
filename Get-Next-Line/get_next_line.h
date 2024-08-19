/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:22:49 by jlebre            #+#    #+#             */
/*   Updated: 2024/08/04 13:29:24 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIT_NEXT_LINE_H
# define GIT_NEXT_LINE_H

# include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


char    *push_line(char *remains);
char    *cut_next_line(char *remains);
bool    find_new_line(char *line);
char    *get_next_line(int fd);

#endif
