NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c \
		children_functions.c \
		free.c \
		pipex_utils.c \
			
			
OBJ = ${SOURCES:.c=.o}

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft