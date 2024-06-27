##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_pacman.so
V2_NAME = $(LIB_DIR)/arcade_pacman_v2.so

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

%.o: %.c
	$(CC) $(SHARED_FLAGS) -c $< -o $@ $(CPPFLAGS)

OBJ_V2 = $(SRC:.c=_v2.o)

%_v2.o: %.c
	$(CC) $(SHARED_FLAGS) -c $< -o $@ $(CPPFLAGS) -DV2

CC = g++

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(V2_NAME)

re: fclean all

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(SRC) | $(LIB_DIR) $(OBJ) $(OBJ_V2)
	$(CC) $(SHARED_FLAGS) $(OBJ) -o $(NAME) $(CPPFLAGS)
	@echo "$(NAME) created"

$(V2_NAME): $(SRC) | $(LIB_DIR) $(OBJ_V2)
	$(CC) $(SHARED_FLAGS) $(OBJ_V2) -o $(V2_NAME) $(CPPFLAGS) -DV2
	@echo "$(V2_NAME) created"

.PHONY: re
