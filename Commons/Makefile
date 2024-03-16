##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

all: lib_arcade_sfml.so lib_arcade_ncurses.so lib_arcade_mygame.so example

clean:

fclean: clean
	@rm -f lib_arcade_sfml.so lib_arcade_ncurses.so lib_arcade_mygame.so example

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

lib_arcade_sfml.so:
	@g++ -shared src/SFML.cpp -o lib_arcade_sfml.so -fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system

lib_arcade_ncurses.so:
	@g++ -shared src/NCurses.cpp -o lib_arcade_ncurses.so -fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror -lncurses

lib_arcade_mygame.so:
	@g++ -shared src/MyGame.cpp -o lib_arcade_mygame.so -fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror

example:
	@g++ src/Core.cpp -o example -iquote ./include -std=c++20 -Wall -Wextra -Werror
