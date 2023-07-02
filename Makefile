SRC			=	main.c \
				tools.c \
				draw_line.c \
				asign_values.c \
				line_utils.c \
				close_window_x.c \
				hook_utils.c \
				playground.c \


INCLUDES	=	-I./includes

LIBFT_DIR		=	./libs/libft

LIBFT		=	$(LIBFT_DIR)/libftprintf.a

HEADERS		=	./includes/cub3D.h \

VPATH		=	./src \
				./src/minilibx \
				./src/line \
				./src/hooks \
				./src/playground \

OBJS_DIR	=	./objects

OBJS		=	$(patsubst %.c,$(OBJS_DIR)/%.o, $(SRC))

CFLAGS		=	-Wall -Wextra -Werror -g3 -lXext -L. -lX11

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
