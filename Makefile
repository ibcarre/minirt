NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRCS = *.c

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
