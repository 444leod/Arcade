##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

DIR = $(shell pwd)
INC_DIR = $(DIR)/include

all: pacman

clean:
	@make -s -C src clean 		LIB_DIR=$(LIB_DIR)

fclean: clean
	@make -s -C src fclean 	LIB_DIR=$(LIB_DIR)

re: fclean all

pacman:
	@make -C src 		LIB_DIR=$(LIB_DIR) INC_DIR=$(INC_DIR)

tests_run:
	@exit 0

.PHONY: all clean fclean re
.SILENT: run
