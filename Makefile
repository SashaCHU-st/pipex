NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c \
			helping_functions.c \
			child_fumction.c \
			
			
OBJ = ${SOURCES:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re