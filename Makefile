##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

DIR = $(shell pwd)
LIB_DIR = $(DIR)/lib
INC_DIR = $(DIR)/include

all: games graphicals core

clean:
	@make -s -C src/Games/Snake clean 		LIB_DIR=$(LIB_DIR)
	@make -s -C src/Games/Nibbler clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/SFML clean 	LIB_DIR=$(LIB_DIR)
#	@make -s -C src/Graphics/NCurses clean 	LIB_DIR=$(LIB_DIR)
#	@make -s -C src/Graphics/SDL2 clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Core clean 				DIR=$(DIR)

fclean: clean
	@make -s -C src/Games/Snake fclean 		LIB_DIR=$(LIB_DIR)
	@make -s -C src/Games/Nibbler fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Graphics/SFML fclean 	LIB_DIR=$(LIB_DIR)
#	@make -s -C src/Graphics/NCurses fclean LIB_DIR=$(LIB_DIR)
#	@make -s -C src/Graphics/SDL2 fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C src/Core fclean 			DIR=$(DIR)

re: fclean all

core:
	@make -s -C src/Core 				DIR=$(DIR) INC_DIR=$(INC_DIR)

core_re:
	@make -s -C src/Core re 			DIR=$(DIR) INC_DIR=$(INC_DIR)

games:
	@make -s -C src/Games/Snake 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Games/Nibbler 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

games_re:
	@make -s -C src/Games/Snake re 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Games/Nibbler re 	LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

graphicals:
#	@make -s -C src/Graphics/NCurses 	LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Graphics/SFML 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
#	@make -s -C src/Graphics/SDL2 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

graphicals_re:
#	@make -s -C src/Graphics/NCurses re LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
	@make -s -C src/Graphics/SFML re 	LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)
#	@make -s -C src/Graphics/SDL2 re LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

tests_run:
	@exit 0

bonus:
	@make -s -C ./bonus re LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

bonus_fclean:
	@make -s -C ./bonus fclean LIB_DIR=$(LIB_DIR)

init: install-hooks install-mango

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@echo "Hooks installed."

install-mango:
	@chmod +x ./init/install-mango.sh
	@./init/install-mango.sh

.PHONY: all clean fclean re bonus
.SILENT: run
