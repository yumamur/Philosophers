CC = clang
CFLAGS = -Wall -Werror -Wextra
CDEFINES =
SANITIZER = -fsanitize=address

NAME = philo_bonus

SRC = main_bonus.c \
	  routine_bonus.c \
	  set_the_table_bonus.c \
	  time_utils_bonus.c

all: $(NAME)


$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(CDEFINES) $(SANITIZER) $(SRC) -o $(NAME)

clean:

fclean:
	@rm -rf $(NAME)

re: fclean all
