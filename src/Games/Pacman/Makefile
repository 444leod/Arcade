##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_pacman.so

CPPFLAGS = -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror
SHARED_FLAGS = -shared

SRC = Pacman.cpp \
	$(addprefix game/, $(GAME_SRC)) \
	$(addprefix game-over/, $(GAME_OVER_SRC)) \
	$(addprefix pause/, $(PAUSE_SRC)) \
	$(addprefix win/, $(WIN_SRC))

GAME_SRC = Game.cpp \
	AEntity.cpp \
	Player.cpp \
	Ghost.cpp \
	PathFinder.cpp \
	ghosts/Blinky.cpp \
	ghosts/Pinky.cpp \
	ghosts/Inky.cpp \
	ghosts/Clyde.cpp \
	Map.cpp \

GAME_OVER_SRC = GameOver.cpp
PAUSE_SRC = Pause.cpp
WIN_SRC = Win.cpp

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
