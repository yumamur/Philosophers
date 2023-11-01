CC = clang
CFLAGS = -Wall -Werror -Wextra
CDEFINES =
SANITIZER = -fsanitize=address

NAME = philo_bonus

SRC = main.c \
	  routine.c \
	  set_the_table.c \
	  time_utils.c

all: $(NAME)


$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(CDEFINES) $(SANITIZER) $(SRC) -o $(NAME)

clean:

fclean:
	@rm -rf $(NAME)

re: fclean all
