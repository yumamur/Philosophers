NAME 		:=	philo
NAME_BONUS	:=	philo_bonus

DIR_SRC			:=	philo
DIR_SRC_BONUS	:=	philo_bonus
DIR_OBJ			:=	obj
DIR_OBJ_BONUS	:=	obj_bonus
DIR_BIN			:=	bin

FILES_HDR	:=	$(DIR_SRC)/philo.h \
				$(DIR_SRC)/philo_datatypes.h \
				$(DIR_SRC)/typeft.h

FILES_SRC	:=	$(DIR_SRC)/atoui_v2.c \
				$(DIR_SRC)/create_data.c \
				$(DIR_SRC)/main.c \
				$(DIR_SRC)/parse_args.c

FILES_HDR_BONUS	:=	$(DIR_SRC_BONUS)/philo.h \
					$(DIR_SRC_BONUS)/philo_datatypes.h \
					$(DIR_SRC_BONUS)/typeft.h

FILES_SRC_BONUS	:=	$(DIR_SRC_BONUS)/atoui_v2.c \
					$(DIR_SRC_BONUS)/create_data.c \
					$(DIR_SRC_BONUS)/main.c \
					$(DIR_SRC_BONUS)/parse_args.c

##########################################################

CC			:=	clang
CFLAGS		:=	-Wall -Werror -Wextra
SANITIZER	:=	-fsanitize=thread
DEFINES		:=

OBJ			:=	$(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(FILES_SRC))
OBJ_BONUS	:=	$(patsubst $(DIR_SRC_BONUS)/%.c, $(DIR_OBJ_BONUS)/%.o, $(FILES_SRC_BONUS))

create_dir =\
	mkdir -p $@;\
	if [ "$@" != "bin" ];then \
	printf "Building: \033[1;4m%s\033[m\n" "$(TARGET_NAME)";\
	printf "\
Compiler   -> %s\n\
Cflags     -> %s\n\
Sanitizer  -> %s\n\
CL Defines -> %s\n"\
	"$(CC)" "$(CFLAGS)" "$(SANITIZER)" "$(DEFINES)";\
	fi

.PHONY: all bonus test clean fclean re

all: TARGET_NAME := $(NAME)
all: TARGET_OBJ := $(OBJ)
all: TARGET = all
all:$(OBJ) $(DIR_BIN)/$(NAME)
	@printf "Done building: \033[32;1m%s\033[m\n" "$(TARGET_NAME)"
	@if [ "$(TARGET)" != "$(MAKECMDGOALS)" ]; then \
		echo; \
	fi

bonus: TARGET_NAME := $(NAME_BONUS)
bonus: TARGET_OBJ := $(OBJ_BONUS)
bonus: TARGET = bonus
bonus: $(OBJ_BONUS) $(DIR_BIN)/$(NAME_BONUS)
	@printf "Done building: \033[32;1m%s\033[m\n" "$(TARGET_NAME)"
	@if [ "$(TARGET)" != "$(MAKECMDGOALS)" ]; then \
		echo; \
	fi

$(DIR_BIN)/%: $(TARGET_OBJ) | $(DIR_BIN)
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) $(TARGET_OBJ) -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	@printf "Compiling: %s -> %s\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) -c $< -o $@

$(DIR_OBJ_BONUS)/%.o: $(DIR_SRC_BONUS)/%.c | $(DIR_OBJ_BONUS)
	@printf "Compiling: %s -> %s\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) -c $< -o $@

$(DIR_OBJ) $(DIR_OBJ_BONUS) $(DIR_BIN):
	@$(call create_dir)

clean:
	@rm -rf $(DIR_OBJ) $(DIR_OBJ_BONUS) $(DIR_OBJ_TEST)

fclean: clean
	@rm -rf $(DIR_BIN)

re: fclean all

CC_T		:=	clang
CFLAGS_T	:=	-Wall -Werror -Wextra
SANITIZER_T	:=	-fsanitize=address
DEFINES_T	:=

NAME_TEST		:=	$(NAME)_test
DIR_OBJ_TEST	:=	obj_test
OBJ_TEST		:=	$(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ_TEST)/%.o, $(FILES_SRC))

test: CC := $(CC_T)
test: CFLAGS := $(CFLAGS_T)
test: SANITIZER := $(SANITIZER_T)
test: DEFINES := $(DEFINES_T)
test: TARGET_NAME := $(NAME_TEST)
test: TARGET_OBJ := $(OBJ_TEST)
test: SANITIZER := -fsanitize=address
test: TARGET := test
test: $(OBJ_TEST) $(DIR_BIN)/$(NAME_TEST)
	@printf "Done building: \033[32;1m%s\033[m\n" "$(TARGET_NAME)"
	@if [ "$(TARGET)" != "$(MAKECMDGOALS)" ]; then \
		echo; \
	fi

$(DIR_OBJ_TEST)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ_TEST)
	@printf "Compiling: %s -> %s\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(SANITIZER) $(DEFINES) -c $< -o $@

$(DIR_OBJ_TEST):
	@$(call create_dir)
