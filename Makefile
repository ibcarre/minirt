NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRCS = main.c \
	utils/get_next_line.c\
	utils/get_next_line_utils.c\
	utils/debugging.c\
	utils/list_utils.c\
	utils/minirt_utils.c\
	parsing/parsing_utils.c\
	parsing/parsing.c\
	parsing/parsing_fill.c\
	parsing/parsing_fill_utils.c\
	utils/ft_atof.c\

OBJ_DIR = obj

OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)

MINILIBX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX):
	make -C ./minilibx-linux

clean:
	rm -rf $(OBJ_DIR)
	make -C ./minilibx-linux clean

fclean: clean
	rm -f $(NAME)

re: fclean all
