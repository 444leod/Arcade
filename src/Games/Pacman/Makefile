##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_pacman.so

CPPFLAGS = -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror
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

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(SRC) -o $(NAME) $(CPPFLAGS)
	@echo "$(NAME) created"
