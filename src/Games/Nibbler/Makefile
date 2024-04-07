##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_nibbler.so

CPPFLAGS = -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror
SHARED_FLAGS = -shared

SRC =	./NibblerGame.cpp \
		./GameObjects/NibblerObjectManager.cpp \
		./GameObjects/Nibbler.cpp \
		./GameObjects/Rock.cpp \
		./GameObjects/SuperCandy.cpp \
		./../SnakeLib/AGameObject.cpp \
		./../SnakeLib/AGameObjectManager.cpp \
		./../SnakeLib/ASnakeObject.cpp

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
