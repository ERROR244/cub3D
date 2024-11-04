NAME	= cub3D

SRCM	=	Get-Next-Line/get_next_line.c\
			Get-Next-Line/get_next_line_utils.c\
			map_checker/map_check.c\
			map_checker/map_check1.c\
			map_checker/map_check2.c\
			map_checker/map_check3.c\
			main/main.c\
			error/error0.c\
			error/error1.c\
			Libft/ft_strlen.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_split.c\
			Libft/split_utils.c\
			Libft/ft_atoi.c\
			Libft/ft_strncmp.c\
			Libft/ft_isdigit.c\
			graphic_management/graphic_management.c\
			graphic_management/event.c\
			graphic_management/cast_rays.c\
			graphic_management/wall_check.c\
			graphic_management/player_move.c\
			graphic_management/get_hit_pos.c\
			graphic_management/init_gm_data.c\
			graphic_management/render3D.c\
			graphic_management/minimap.c\
			graphic_management/minimap2.c\

OBJM	= ${SRCM:.c=.o}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MLX_LIB	= -L./minilibx-linux -lmlx -lX11 -lXext -lm -lz

all:		${NAME}

${NAME}:	${OBJM}
	${CC} ${CFLAGS} ${OBJM} $(MLX_LIB) -o ${NAME}

clean:
	@rm -f ${OBJM}

fclean:		clean
	@rm -f ${NAME}

re:		fclean all

.SECONDARY : ${OBJM}
.PHONY: all clean fclean re
