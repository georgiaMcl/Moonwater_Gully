#include "Game.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  Game game(600, "Moonwater Gully");
  game.makeBackground();
  game.run();
  return 0;
}