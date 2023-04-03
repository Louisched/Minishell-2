##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME = mysh

SRC	=	main.c \
		my/my_strlen.c \
		my/my_putchar.c \
		my/my_putstr.c \
		my/my_put_nbr.c \
		my/my_strcpy.c \
		my/my_strcmp.c \
		my/mini_printf.c \
		my/my_strncpy.c \
		linked_lists/dlist_functions.c \
		linked_lists/dlist_functionsb.c \
		src/env_functions.c \
		src/exec.c \
		src/put_error.c \
		src/path_handler.c \
		src/prepare_cmd.c \
		src/setenv_functions.c \
		src/builtins.c \
		src/cd_functions.c \
		src/builtins_handling.c \
		src/separate_cmd.c \
		src/redirections.c \
		src/prompt.c \
		src/errors.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I./includes

CFLAGS	=	-W $(INCLUDES) -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: fclean
	coding-style . .
	cat coding-style-reports.log
	rm coding-style-reports.log -f
