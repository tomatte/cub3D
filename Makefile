SRC			=	main.c \
				tools.c \
				draw_line.c \
				asign_values.c \
				line_utils.c \
				close_window_x.c \
				hook_utils.c \
				validation_files_01.c \
				validation_map_02.c  \
				validation_map_05.c       \
				validation_utils_01.c \
				validation_files_02.c \
				validation_map_03.c \
				validation_map_file_01.c \
				validation_utils_02.c \
				validation_map_01.c \
				validation_map_04.c \
				validation_start.c \
				validation_print_map.c \
				playground.c \
				color.c \
				move_hook.c \
				move_calc.c \
				squares.c \
				ray_tools.c \
				dda_ray.c \
				multiple_rays_to_3d.c \
				compass.c \
				find_vertical_wall.c \
				find_horizontal_wall.c \
				ray_tools2.c \
				ray_tools3.c \
				init_player.c \


INCLUDES	=	-I./includes

LIBFT_DIR		=	./libs/libft

LIBFT		=	$(LIBFT_DIR)/libftprintf.a

HEADERS		=	./includes/cub3D.h \

VPATH		=	./src \
				./src/minilibx \
				./src/line \
				./src/hooks \
				./src/validation \
				./src/playground \

OBJS_DIR	=	./objects

OBJS		=	$(patsubst %.c,$(OBJS_DIR)/%.o, $(SRC))

CFLAGS		=	-Wall -Wextra -g3 -lXext -L. -lX11 -lm -Werror
#CFLAGS		=	-g3 -O3 -Imlx -Lmlx -lmlx -lXext -lX11 -lm -fPIE

MINILIBX_DIR	=	./libs/minilibx-linux
MINILIBX		=	$(MINILIBX_DIR)/libmlx_Linux.a

NAME		=	cub3D



CC			=	cc

RM			=	rm -rf

all:	$(NAME)

$(MINILIBX):
	make -C $(MINILIBX_DIR) all

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(OBJS_DIR)/%.o:	%.c
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(OBJS_DIR):
	mkdir -p $@

$(NAME):	$(MINILIBX) $(OBJS_DIR) $(OBJS) $(HEADERS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(MINILIBX) $(CFLAGS) $(INCLUDES) -o $@

clean:
	$(RM) $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINILIBX_DIR) clean

fclean:	clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	fclean clean re
