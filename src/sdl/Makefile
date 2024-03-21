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
				-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer	\
				-shared -fPIC -g

SRC	=	SDL.cpp

all:
	$(CC) -o $(NAME) $(SRC) $(CPPFLAGS)
##	mv $(NAME) ../../lib
	cp arcade_sdl.so ../../../Arcade-Commons/

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../../lib/$(NAME)

re:	fclean all
