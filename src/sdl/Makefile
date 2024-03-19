##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME	=	arcade_sdl.so

CC	=	g++

CPPFLAGS	=	-W -Wall -Wextra -Wpedantic	\
				-std=c++20 -I../../include/	\
				-lSDL2 -lSDL2_image	\
				-shared -fPIC

SRC	=	SDL.cpp

all:
	$(CC) -o $(NAME) $(SRC) $(CPPFLAGS)
	mv $(NAME) ../../lib

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../../lib/$(NAME)

re:	fclean all
