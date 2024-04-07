##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

all: pacman

clean:
	@make -s -C Pacman clean 	LIB_DIR=$(LIB_DIR)

fclean: clean
	@make -s -C Pacman fclean 	LIB_DIR=$(LIB_DIR)

pacman :
	@make -s -C Pacman 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

re: fclean all

.PHONY: re
