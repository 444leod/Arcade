##
## EPITECH PROJECT, 2024
## PROJECT_NAME
## File description:
## Makefile
##

NAME = EXECUTABLE_NAME

SRC = ./src/main.c

OBJ = $(SRC:.asm=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

run: all

init: install-hooks install-mango

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@echo "Hooks installed."

install-mango:
	@chmod +x ./init/install-mango.sh
	@./init/install-mango.sh

.PHONY: all clean fclean re
.SILENT: run
