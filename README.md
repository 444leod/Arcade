# Arcade

*If you are looking for a guide on the interface or on how to implement games/graphical libraries, go to ./doc/arcade_guide.md*

## Description

Arcade is a project that aims to create a gaming platform that allows the user to choose between different games and graphical libraries. The user can switch between games and libraries at runtime.

## Authors
We (Stereo Madness) chose to work with the following groups:
![](./assets/lesquatrespoggersfeatmerlin+aer+elliot.png)
- **CodinBox**:
  - yanis.zeghiche (group leader)
  - adam.brutsaert
- **Hors cadre**:
  - merlin.cyffers (group leader)
  - adam.cavillon
  - alexandre.barberis
- **Stereo Madness**:
  - leo.dumont (group leader)
  - elliot.alladaye
  - thibault.longuepee

We have the same interfaces and our games and graphical libraries are compatible with each other.

## How to use

Do `make` to compile the project, then run `./arcade ./lib/lib_arcade_sfml.so` to start the program with the SFML graphical library (or any other library). You can then switch between games and libraries at runtime.

## Our games

### Snake

Use `Z`, `Q`, `S`, `D` to move the snake.

Try to eat as many candies as possible to increase your score will avoiding the walls and the snake's body.

Consumables:
- ![](./assets//snake/images/super_candy.png) **Super-Candy**:  Increases the snake's size by 1 and is worth 10 score points. It has the side effect of increasing the snake's speed, be careful!
- ![](./assets//snake/images/aguav_berry.png) **Aguav Berry**: Decreases the snake's size by 1 and is worth -5 score points (It's worth it!).
- ![](./assets//snake/images/tamato_berry.png) **Tamato Berry**: Resets the snake's speed, but is worth -5 score points (It's also worth it!).

Berries may appear after eating a super-candy but only one of each type can be present at a time.

### Pacman

Use `Z`, `Q`, `S`, `D` to move Pacman.

Try to eat as many dots as possible to increase your score while avoiding the ghosts.
Eating a big dot will allow you to eat the ghosts for a short period of time.

## Our Graphical Libraries

To switch graphical libraries, use the ... key.

### SFML

### Ncurses

### SDL2

