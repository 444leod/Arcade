##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = $(LIB_DIR)/arcade_sfml.so

CPPFLAGS += -fPIC -iquote $(INC_DIR) -std=c++20 -Wall -Wextra -Werror
SHARED_FLAGS = -shared
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = \
	SFML.cpp \
	SFMLAudio.cpp \
	SFMLDisplay.cpp \
	SFMLFont.cpp \
	SFMLTexture.cpp \

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(SRC) -o $(NAME) $(CPPFLAGS) $(SFML_FLAGS)
	@echo "$(NAME) created"
