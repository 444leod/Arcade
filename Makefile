##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SFML = lib/arcade_sfml.so
NCURSES = lib/arcade_ncurses.so
EXAMPLE = lib/arcade_example.so
PACMAN = lib/arcade_pacman.so
CORE = arcade

all: $(LIB_DIR) core games graphics

clean:

fclean: clean
	@rm -f $(SFML)
	@rm -f $(NCURSES)
	@rm -f $(EXAMPLE)
	@rm -f $(PACMAN)
	@rm -f $(CORE)
	@rm -f core

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

core: $(CORE)
games: $(EXAMPLE) $(PACMAN)
graphics: $(SFML) $(NCURSES)

LIB_DIR = lib
$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

CC = g++

SHARED_FLAGS = -shared
CPPFLAGS = -fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
NCURSES_FLAGS = -lncurses
# SDL2_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SFML_SRC = src/Graphics/SFML/SFML.cpp
$(SFML): $(SFML_SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(SFML_SRC) -o $(SFML) $(CPPFLAGS) $(SFML_FLAGS)
	@echo "$(SFML) created"

NCURSES_SRC = src/Graphics/NCurses/NCurses.cpp
$(NCURSES): $(NCURSES_SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(NCURSES_SRC) -o $(NCURSES) $(CPPFLAGS) \
		$(NCURSES_FLAGS)
	@echo "$(NCURSES) created"

EXAMPLE_SRC = src/Games/Example/Example.cpp
$(EXAMPLE): $(EXAMPLE_SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(EXAMPLE_SRC) -o $(EXAMPLE) $(CPPFLAGS)
	@echo "$(EXAMPLE) created"

PACMAN_SRC = src/Games/Pacman/Pacman.cpp
$(PACMAN): $(PACMAN_SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(PACMAN_SRC) -o $(PACMAN) $(CPPFLAGS)
	@echo "$(PACMAN) created"

CORE_SRC = src/Core/Core.cpp
$(CORE): $(CORE_SRC)
	@$(CC) $(CORE_SRC) -o $(CORE) $(CPPFLAGS)
	@echo "$(CORE) created"

example: $(CORE) $(EXAMPLE) $(SFML) $(NCURSES)
	@$(CC) $(CORE_SRC) -o example $(CPPFLAGS)
	@echo "example created"

pacman: $(PACMAN) $(SFML) $(NCURSES)
	@$(CC) $(CORE_SRC) -o pacman $(CPPFLAGS) -DPACMAN
	@echo "pacman created"

tests_run:
	@exit 0

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
