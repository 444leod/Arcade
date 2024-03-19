##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = arcade

SRC			=	${SRC_MAIN}

SRC_MAIN 	= ./src/main.cpp

OBJ			=	$(SRC:.cpp=.o)

BONUS_SRC = \

BONUS_OBJ  =	$(BONUS_SRC:.cpp=.o)

PYTHON_TESTER = ./tests/tester.py

TESTS_NAME	=	unit_tests

TESTS_SRC	=	$(filter-out ./src/main.cpp, $(SRC)) ./tests/tests.cpp \

TESTS_OBJ	=	$(TESTS_SRC:.cpp=.o)

CC			=	g++

CPPFLAGS	=	-std=c++20 -W -Wall -Wextra -Wpedantic -I./include/

DEBUGFLAGS = 	-g

TESTS_FLAGS	=	-lcriterion --coverage -fprofile-arcs -ftest-coverage

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME)
	make -C src/sdl

debug:
	$(CC) $(SRC) $(CPPFLAGS) $(DEBUGFLAGS) -o $(NAME)

run:	all
	./$(NAME) -d $(D)

tests_run:	fclean $(TESTS_OBJ)
	$(CC) $(TESTS_OBJ) $(CPPFLAGS) -o $(TESTS_NAME)
	@./$(TESTS_NAME)
	@$(PYTHON_TESTER)


$(TESTS_NAME):
	@$(CC) -o $(TESTS_NAME) $(TESTS_SRC) $(CPPFLAGS) $(TESTS_FLAGS)

cov:
	gcovr --exclude tests -u

covb:
	gcovr --exclude tests -ub

clean:
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno
	make clean -C src/sdl

fclean:	clean
	rm -f $(NAME)
	rm -f $(TESTS_NAME)
	make fclean -C src/sdl

re:	fclean all
	make re -C src/sdl

bonus: fclean $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) $(CPPFLAGS) -o $(NAME)

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
