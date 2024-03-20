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

DIR = $(shell pwd)
LIB_DIR = $(DIR)/lib
INC_DIR = $(DIR)/include

all: games graphics core

clean:
	@make -s -C src/Games/Pacman clean 		LIB_DIR=$(LIB_DIR)
	@make -s -C src/Games/Snake clean 		LIB_DIR=$(LIB_DIR)
	@make -s -C src/Games/Example clean		LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/SFML clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/NCurses clean 	LIB_DIR=$(LIB_DIR)
	@# @make -s -C src/Graphics/SDL2 clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Core clean 				DIR=$(DIR)

fclean: clean
	@make -s -C src/Games/Pacman fclean 	LIB_DIR=$(LIB_DIR)
	@# @make -s -C src/Games/Snake fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Games/Example fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/SFML fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/NCurses fclean LIB_DIR=$(LIB_DIR)
	@# @make -s -C src/Graphics/SDL2 fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Core fclean 			DIR=$(DIR)

re: fclean all

core:
	@make -s -C src/Core 				DIR=$(DIR) INC_DIR=$(INC_DIR)

games:
	@make -s -C src/Games/Pacman 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@# @make -s -C src/Games/Snake 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Games/Example 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

graphics:
	@make -s -C src/Graphics/NCurses 	LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Graphics/SFML 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@# @make -s -C src/Graphics/SDL2 	LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

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
