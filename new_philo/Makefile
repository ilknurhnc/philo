NAME = philo
SRC = philo.c utils.c init.c act.c control.c
OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all