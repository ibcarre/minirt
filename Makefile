NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRCS = main.c \
	get_next_line.c\
	get_next_line_utils.c\
	debugging.c\
	check_parsing.c\
	list_utils.c\
	minirt_utils.c\
	parsing_utils.c\
	parsing.c\
	parsing_fill.c\
	parsing_fill_utils.c\
	ft_atof.c\

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))

MINILIBX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX):
	make -C ./minilibx-linux

clean:
	rm -f $(OBJ)
	make -C ./minilibx-linux clean

fclean: clean
	rm -f $(NAME)

re: fclean all
