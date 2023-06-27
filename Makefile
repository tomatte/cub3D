SRC			=	main.c \


INCLUDES	=	-I./includes

LIBFT_DIR		=	./libft

LIBFT		=	$(LIBFT_DIR)/libftprintf.a

HEADERS		=	./includes/cub3D.h \

VPATH		=	./src \

OBJS_DIR	=	./objects

OBJS		=	$(patsubst %.c,$(OBJS_DIR)/%.o, $(SRC))

CFLAGS		=	-Wall -Wextra -Werror -g3 -lXext -L. -lX11

MINILIBX	=	./minilibx-linux/libmlx_Linux.a

NAME		=	cub3D



CC			=	cc

RM			=	rm -rf

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(OBJS_DIR)/%.o:	%.c
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(OBJS_DIR):
	mkdir -p $@

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADERS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(MINILIBX) $(CFLAGS) $(INCLUDES) -o $@

clean:
	$(RM) $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean

fclean:	clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	fclean clean re
