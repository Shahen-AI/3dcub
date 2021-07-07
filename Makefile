NAME = cub3d
CC = gcc
AR = ar csr
CP = cp
SRCS = main.c parser.c sprites.c screenshot.c ${shell find "./gnl" -name "*.c"}
OBJS = ${SRCS:.c=.o}
COMPILE_FLAGS = -Wall -Wextra -Werror
MLX_FALGS = -Llibs/minilibx_mms -lmlx -framework OpenGL -framework AppKit
MLX_PATH = libs/minilibx_mms/
LIBFT_PATH = libs/libft/
LIBFT_FLAGS = -Llibs/libft -lft

$(NAME) : 	${OBJS}
			# @mv libs/minilibx_mms/libmlx.dylib .
			${CC} ${SRCS} ${MLX_FALGS} ${LIBFT_FLAGS} -o ${NAME}
			#./cub3d

all : ${NAME}

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re .c.o