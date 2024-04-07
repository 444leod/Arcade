##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

all: pacman openpacman fighto

clean:
	@make -s -C Pacman clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C Fighto clean 	LIB_DIR=$(LIB_DIR)
	@make -s -C openPacman clean 	LIB_DIR=$(LIB_DIR)

fclean: clean
	@make -s -C Pacman fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C Fighto fclean 	LIB_DIR=$(LIB_DIR)
	@make -s -C openPacman fclean 	LIB_DIR=$(LIB_DIR)

fighto:
	@make -s -C Fighto 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

pacman :
	@make -s -C Pacman 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

openpacman:
	@make -s -C openPacman 	LIB_DIR=$(LIB_DIR)

re: fclean all

.PHONY: re
