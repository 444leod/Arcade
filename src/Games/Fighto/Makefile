##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_fighto.so

CPPFLAGS += -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror -pthread
CPPFLAGS += -I./ -I ./Versus/ -I./Versus/Moves/ -I./Loading/ -I./Components/
SHARED_FLAGS = -shared

SRC =	SceneManager.cpp	\
	Components/Button.cpp \
	$(addprefix Loading/, $(SRC_LOADING)) \
	$(addprefix Versus/, $(SRC_VERSUS)) \

SRC_VERSUS = Versus.cpp \
			Champion.cpp \
			ChampionManager.cpp \
			HitBox.cpp \
			HitSolver.cpp \
			Animations/AAnimation.cpp \
			Animations/Idle.cpp \
			Moves/AMove.cpp \
			Moves/Jab.cpp \
			Moves/Kick.cpp \

SRC_LOADING = Loading.cpp \

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
