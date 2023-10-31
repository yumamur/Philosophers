CC = clang
CFLAGS = -Wall -Werror -Wextra
CDEFINES =
# CSANITIZER = -fsanitize=thread

NAME = philo

SRC = main.c \
	  routine.c \
	  set_the_table.c \
	  time_utils.c

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(CDEFINES) $(CSANITIZER) $(SRC) -o $(NAME)
