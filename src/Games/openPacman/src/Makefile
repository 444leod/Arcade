##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_openpacman.so

CPPFLAGS = -fPIC -iquote ../include -std=c++20 -Wall -Wextra -Werror -g
SHARED_FLAGS = -shared

SRC = ./Pacman.cpp \
	./AEntity.cpp \
	./Player.cpp \
	./MapHandler.cpp \
	./Ghost.cpp \
	./ghosts/Blinky.cpp \
	./ghosts/Pinky.cpp \
	./ghosts/Inky.cpp \
	./ghosts/Clyde.cpp \
	./PathFinder.cpp \
	./Map.cpp \

OBJ = $(SRC:.cpp=.o)

CC = g++

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(SRC) | $(LIB_DIR) $(OBJ)
	$(CC) $(SHARED_FLAGS) $(OBJ) -o $(NAME) $(CPPFLAGS)
	@echo "$(NAME) created"
