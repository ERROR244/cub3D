NAME	= cub3D
TESTER	= tester

SRCM	=	Get-Next-Line/get_next_line.c\
			Get-Next-Line/get_next_line_utils.c\
			map_checker/map_check.c\
			map_checker/map_check1.c\
			map_checker/map_check2.c\
			map_checker/map_check3.c\
			main/main.c\
			tmp/tmp1.c\
			error/error0.c\
			error/error1.c\
			Libft/ft_strlen.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_split.c\
			Libft/split_utils.c\
			Libft/ft_atoi.c\
			Libft/ft_strncmp.c\
			graphic_management/graphic_management.c\
			graphic_management/event.c\
			graphic_management/cast_rays.c\
			graphic_management/wall_check.c\
			graphic_management/player_move.c\
			graphic_management/get_hit_pos.c\
			graphic_management/init_gm_data.c\
			graphic_management/render3D.c\
			bonus/minimap.c

OBJM	= ${SRCM:.c=.o}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -ggdb -g3 -fsanitize=address
MLX_LIB	= -L./minilibx-linux -lmlx -lX11 -lXext -lm -lz

all:		${NAME}

${NAME}:	${OBJM}
	${CC} ${CFLAGS} ${OBJM} $(MLX_LIB) -o ${NAME}

TESTER : ${NAME}
	g++ ${CFLAGS} Unit-Tests/main.cpp -o ${TESTER}

clean:
	@rm -f ${OBJM}

remove:
	@rm -rf ${TESTER}

fclean:		clean remove
	@rm -f ${NAME}

re:		fclean all

.SECONDARY : ${OBJM}
.PHONY: all clean fclean re
