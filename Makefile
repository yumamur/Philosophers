NAME 		=	philo
NAME_BONUS	=	philo_bonus

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra
SANITIZER	=	-fsanitize=thread
DEFINES		=

DIR_MANDATORY	=	philo
DIR_BONUS		=	philo_bonus
DIR_OBJ			=	objdir
DIR_BIN			=	bin

HDR			=	$(DIR_MANDATORY)/philo.h \
				$(DIR_MANDATORY)/philo_datatypes.h \
				$(DIR_MANDATORY)/typeft.h

SRC			=	$(DIR_MANDATORY)/atol_v2.c \
				$(DIR_MANDATORY)/main.c \
				$(DIR_MANDATORY)/parse_args.c

SRC_BONUS	=	$(DIR_BONUS)/main.c

OBJ			=	$(patsubst $(DIR_MANDATORY)/%.c, $(DIR_OBJ)/%.o, $(SRC))
OBJ_BONUS	=	$(patsubst $(DIR_BONUS)/%.c, $(DIR_OBJ)/%.o, $(SRC_BONUS))


.PHONY = all bonus clean fclean re

all: $(DIR_OBJ) $(NAME)

bonus: $(DIR_OBJ) $(NAME_BONUS)

clean:
	@rm -rf $(DIR_OBJ)

fclean:
	@rm -rf $(DIR_OBJ) $(DIR_BIN)

re: fclean all

compile_objects = \
	for i in $@; do \
		src_file=$$(echo $$i | sed 's,$(DIR_OBJ),$(DIR_MANDATORY),' | sed 's,\.o,\.c,'); \
		if [ -e "$$src_file" ]; then \
			echo "Compiling $$src_file"; \
			$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) -c $$src_file -o $$i; \
		else \
			echo "Could not find file $$src_file"; \
			echo "Exiting"; \
			exit 1; \
		fi; \
	done

$(NAME): $(DIR_BIN) $(OBJ)
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) $(OBJ) -o $(DIR_BIN)/$(NAME)

$(NAME_BONUS): $(DIR_BIN) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) $(OBJ) -o $(DIR_BIN)/$(NAME_BONUS)

$(OBJ): $(SRC)
	@$(call compile_objects)

$(OBJ_BONUS): $(SRC_BONUS)
	@$(call compile_objects)

$(DIR_OBJ):
	@mkdir -p $@

$(DIR_BIN):
	@mkdir -p $@
