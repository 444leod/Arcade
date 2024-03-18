##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

all: lib_arcade_sfml.so lib_arcade_ncurses.so lib_arcade_mygame.so example

clean:

fclean: clean
	@rm -f \
	lib_arcade_sfml.so lib_arcade_ncurses.so lib_arcade_mygame.so example

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

lib_arcade_sfml.so: src/SFML.cpp
	@g++ -shared src/SFML.cpp -o lib_arcade_sfml.so \
	-fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror \
	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	@echo "lib_arcade_sfml.so created"

lib_arcade_ncurses.so: src/NCurses.cpp
	@g++ -shared src/NCurses.cpp -o lib_arcade_ncurses.so \
	-fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror \
	-lncurses
	@echo "lib_arcade_ncurses.so created"

lib_arcade_mygame.so: src/MyGame.cpp
	@g++ -shared src/MyGame.cpp -o lib_arcade_mygame.so \
	-fPIC -iquote ./include -std=c++20 -Wall -Wextra -Werror
	@echo "lib_arcade_mygame.so created"

example: src/Core.cpp src/MyGame.cpp src/SFML.cpp src/NCurses.cpp
	@g++ src/Core.cpp -o example \
	-iquote ./include -std=c++20 -Wall -Wextra -Werror
	@echo "example created"
