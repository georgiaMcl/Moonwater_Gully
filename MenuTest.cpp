#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include "Menu.h"
#include "Player.h"
#include "tile.h"

class MenuDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Player* player;
  Menu menu = Menu(300, 150);
  bool visibleMenu = true;
  bool htpVis = false;
  bool controlVis = false;
  bool saveVis = false;

 public:
  MenuDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    player = new Player(10, 50, 50);
    visibleMenu = true;
    htpVis = false;
    controlVis = false;
    saveVis = false;
  };

  void makeBackground() {
    // Create game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
    return;
  };

  void run() {
    // Runs game
    while (win->isOpen()) {
      Event e;
      while (win->pollEvent(e)) {
        if (e.type == Event::Closed) {
          win->close();
        }
        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Up)) {
            menu.moveUp();
            // break;
          }
          if (Keyboard::isKeyPressed(Keyboard::Down)) {
            menu.moveDown();
            // break;
          }
          if (Keyboard::isKeyPressed(Keyboard::Return)) {
            // opening the rectangles of the options
            int selection = menu.menuPressed();
            if (selection == 0) {
              // close the menu and access game window
              visibleMenu = false;
              menu.set_visibility(visibleMenu);
            }

            if (selection == 1) {
              // open game description
              visibleMenu = false;
              menu.set_visibility(visibleMenu);
              htpVis = true;
              menu.set_htpVisi(htpVis);
            }
            if (selection == 2) {
              // open controls rectangle
              visibleMenu = false;
              menu.set_visibility(visibleMenu);
              controlVis = true;
              menu.set_controlVisi(controlVis);
            }
            if (selection == 3) {
              // open save confirmation
              visibleMenu = false;
              menu.set_visibility(visibleMenu);
              saveVis = true;
              menu.set_saveVisi(saveVis);
            }
          }
        }
      }
      win->clear();

      if (Keyboard::isKeyPressed(Keyboard::A)) {
        player->moveLeft();
      } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        player->moveRight();
      } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        player->moveUp();
      } else if (Keyboard::isKeyPressed(Keyboard::S)) {
        player->moveDown();
      }

      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        controlVis = false;
        menu.set_controlVisi(controlVis);
        htpVis = false;
        menu.set_htpVisi(htpVis);
        saveVis = false;
        menu.set_saveVisi(saveVis);
        visibleMenu = true;
        menu.set_visibility(true);
      }

      if (Keyboard::isKeyPressed(Keyboard::M)) {
        visibleMenu = true;
        menu.set_visibility(true);
      }

      // drawing the tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      }

      player->draw(win);

      // drawing the menu
      if (menu.get_visibility() == true) {
        menu.draw(win);
      }
      // drawing htp pop up
      if (menu.get_htpVisi() == true) {
        menu.drawHtp(win);
      }
      if (menu.get_controlVisi() == true) {
        menu.drawControl(win);
      }

      if (menu.get_saveVisi() == true) {
        menu.drawSave(win);
      }

      // drawing the menu

      win->display();
    }
    return;
  };

  // getter
  std::vector<tile*> get_background() { return background; };

  ~MenuDriver(){};
};

int main() {
  MenuDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}