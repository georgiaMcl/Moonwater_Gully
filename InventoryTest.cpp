#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include "BuyMenu.h"
#include "Inventory.h"
#include "Menu.h"
#include "Player.h"
#include "tile.h"

class InventoryDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Player* player;
  Menu menu = Menu(300, 150);
  BuyMenu buymenu = BuyMenu(250, 400);
  bool visibleMenu = true;
  bool visibleBuy = false;
  Inventory inventory = Inventory(550, 50);

 public:
  InventoryDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    player = new Player(10, 50, 50);
    visibleBuy = false;
    visibleMenu = true;
  };

  void makeBackground() {
    // Creates game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
    return;
  };

  void run() {
    // runs the game
    while (win->isOpen()) {
      Event e;
      while (win->pollEvent(e)) {
        if (e.type == Event::Closed) {
          win->close();
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Up)) {
            menu.moveUp();
            buymenu.moveUp();
            buymenu.set_successCheck(false);  // visibility remove
            buymenu.set_failureCheck(false);
          }
          if (Keyboard::isKeyPressed(Keyboard::Down)) {
            menu.moveDown();
            buymenu.moveDown();
            buymenu.set_successCheck(false);
            buymenu.set_failureCheck(false);
          }

          if (Keyboard::isKeyPressed(Keyboard::Space)) {
            inventory.scrollInventory();
          }

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (visibleMenu == true)) {
            // opening the rectangles of the options
            int selection = menu.menuPressed();
            switch (selection) {
              case 0:
                // close the menu and access game window
                visibleMenu = false;
                menu.set_visibility(visibleMenu);
                break;
              case 1:
                // open game description
                menu.set_visibility(false);
                menu.set_htpVisi(true);
                break;
              case 2:
                // open controls rectangle
                menu.set_visibility(false);
                menu.set_controlVisi(true);
                break;
              case 3:
                // open save confirmation
                menu.set_visibility(false);
                menu.set_saveVisi(true);
                break;
            }
          }
          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (visibleBuy == true)) {
            // opening the rectangles of the options
            int itemNo = buymenu.get_buySelect();
            switch (itemNo) {
              case 0:
                if (buymenu.purchaseStatus(player, 0) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract50shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";  // next up, add items into the player's
                                      // inventory
                  inventory.addCarrotSeedsCount();
                  std::cout << "Carrot seeds in inventory: "
                            << inventory.get_carrotSeedsCount() << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 1:
                if (buymenu.purchaseStatus(player, 1) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract50shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";

                  inventory.addPotatoSeedsCount();
                  std::cout << "Potato seeds in inventory: "
                            << inventory.get_potatoSeedsCount() << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 2:
                if (buymenu.purchaseStatus(player, 2) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract70shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";

                  inventory.addStrawberrySeedsCount();

                  std::cout << "Strawberry seeds in inventory: "
                            << inventory.get_strawberrySeedsCount()
                            << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 3:
                if (buymenu.purchaseStatus(player, 3) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract70shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";

                  inventory.addBlueberrySeedsCount();

                  std::cout << "Blueberry seeds in inventory: "
                            << inventory.get_blueberrySeedsCount() << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 4:
                if (buymenu.purchaseStatus(player, 4) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract400shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";

                  inventory.addShovelCount();
                  std::cout
                      << "Shovels in inventory: " << inventory.get_shovelCount()
                      << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 5:
                if (buymenu.purchaseStatus(player, 5) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->subtract150shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";

                  inventory.addGloveCount();
                  std::cout
                      << "Gloves in inventory: " << inventory.get_gloveCount()
                      << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              default:
                std::cout << "Error in purchase" << std::endl;
            }
          }
        }
      }

      win->clear();

      // player movement
      if (Keyboard::isKeyPressed(Keyboard::A)) {
        player->moveLeft();
      }
      if (Keyboard::isKeyPressed(Keyboard::D)) {
        player->moveRight();
      }
      if (Keyboard::isKeyPressed(Keyboard::W)) {
        player->moveUp();
      }
      if (Keyboard::isKeyPressed(Keyboard::S)) {
        player->moveDown();
      }

      // testing of keyboard for menu toggling

      if (Keyboard::isKeyPressed(Keyboard::B) && (visibleMenu == false)) {
        visibleBuy = true;
        buymenu.set_buyOn(visibleBuy);
      }

      if (Keyboard::isKeyPressed(Keyboard::M) && (visibleBuy == false)) {
        if ((menu.get_controlVisi() == false) &&
            (menu.get_htpVisi() == false) && (menu.get_saveVisi() == false)) {
          visibleMenu = true;
          menu.set_visibility(visibleMenu);
        }
      }

      // drawing the tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      }

      inventory.drawInventory(win);

      // visibility of menus
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        if (visibleBuy == false) {
          menu.set_controlVisi(false);
          menu.set_htpVisi(false);
          menu.set_saveVisi(false);

        } else {
          visibleBuy = false;
          buymenu.set_failureCheck(false);
          buymenu.set_successCheck(false);
          buymenu.set_buyOn(false);
          visibleMenu = false;
          menu.set_visibility(visibleMenu);
        }
      }

      player->draw(win);

      // drawing the menus

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
      if (buymenu.get_buyOn() == true) {
        buymenu.draw(win);
      }

      // drawing purchase success or failure
      if (buymenu.get_failureCheck() == true) {
        buymenu.drawPurchaseError(win);
      }
      if (buymenu.get_successCheck() == true) {
        buymenu.drawPurchaseSuccess(win);
      }

      win->display();
    }
    return;
  };

  // getter
  std::vector<tile*> get_background() { return background; }

  ~InventoryDriver(){};
};

int main() {
  InventoryDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}