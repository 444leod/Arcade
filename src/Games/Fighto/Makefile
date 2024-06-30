##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_fighto.so

CPPFLAGS += -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror
CPPFLAGS += -I./ -I./Moves/
SHARED_FLAGS = -shared

SRC =	Fighto.cpp	\
		Champion.cpp	\
		ChampionManager.cpp \
		HitBox.cpp \
		HitSolver.cpp \
		Animations/AAnimation.cpp \
		Animations/Idle.cpp \
		Moves/AMove.cpp \
		Moves/Jab.cpp \
		Moves/Kick.cpp \

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
