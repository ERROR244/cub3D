NAME	= cub3D
TESTER	= tester

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
			Libft/ft_atoi.c\
			Libft/ft_strncmp.c\
			graphic_management/graphic_management.c\

OBJM	= ${SRCM:.c=.o}

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -ggdb -fsanitize=address -g3
CFLAGS1	= -Imlx_linux -O3
LDFLAGS	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all:		${NAME}

${NAME}:	${OBJM}
	${CC} ${CFLAGS} ${CFLAGS} ${OBJM} $(LDFLAGS) -o ${NAME}

TESTER : ${NAME}
	g++ ${CFLAGS} Unit-Tests/main.cpp -o ${TESTER}

clean:
	@rm -f ${OBJM}

remove:
	@rm -rf ${TESTER}

fclean:		clean remove
	@rm -f ${NAME}

re:		fclean all

push :
	@make fclean
	@git add .
	@git commit -m "cub3D"
	@git push origin Sfayga

.SECONDARY : ${OBJM}
.PHONY: all clean fclean re
