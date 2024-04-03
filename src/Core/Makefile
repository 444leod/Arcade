##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(DIR)/arcade

CPPFLAGS = -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror -g

SRC	=	Core.cpp	\
		CoreMenu.cpp	\
		LibraryLoader.cpp	\

CC = g++

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME) $(CPPFLAGS)
	@echo "$(NAME) created"
