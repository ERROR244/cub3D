NAME	= cub3D

SRCM	=	Get-Next-Line/get_next_line.c\
			Get-Next-Line/get_next_line_utils.c\
			map_checker/map_check.c\
			map_checker/map_check1.c\
			map_checker/map_check2.c\
			map_checker/map_check3.c\
			map_checker/map_check4.c\
			map_checker/map_check5.c\
			main/main.c\
			tmp/tmp1.c\
			error/error0.c\
			Libft/ft_strlen.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_split.c\

OBJM	= ${SRCM:.c=.o}

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g3
# CFLAGS1	= -lmlx -framework OpenGL -framework AppKit

all:		${NAME}

${LIBFT} : 
	make -C Libft

${NAME}:	${LIBFT} ${printf} ${OBJM}
	${CC} ${CFLAGS} ${LIBFT} ${printf} ${OBJM} -o ${NAME}
	
clean:
	rm -f ${OBJM}

fclean:		clean
	rm -f ${NAME}

re:			fclean all

.SECONDARY : ${OBJM}
.PHONY: all clean fclean re