#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Blueberry.h"
#include "BuyMenu.h"
#include "Carrot.h"
#include "Day.h"
#include "Menu.h"
#include "Player.h"
#include "Potato.h"
#include "Strawberry.h"
#include "tile.h"
using namespace sf;
#include "BuyMenu.h"
#include "Inventory.h"
#include "Menu.h"
#include "Player.h"
#include "SellMenu.h"
#include "tile.h"

class EverythingDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Player* player;
  Menu menu = Menu(300, 150);
  BuyMenu buymenu = BuyMenu(250, 400);
  SellMenu sellmenu = SellMenu(250, 300);
  Inventory inventory = Inventory(550, 55);
  Day day;
  bool visibleMenu = true;
  bool visibleBuy = false;
  bool visibleSell = false;

 public:
  EverythingDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    player = new Player(10, 50, 50);
    visibleBuy = false;
    visibleMenu = true;
    visibleSell = false;
  };

  void makeBackground() {
    // creates game background
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
          if (Keyboard::isKeyPressed(Keyboard::P)) {
            switch (inventory.get_inventoryIndex()) {
              case 2:
                if (inventory.get_blueberrySeedsCount() > 0) {
                  player->seedPlant(2, &background);
                  inventory.subtractBlueberrySeedsCount();
                } else {
                  std::cout
                      << "No blueberry seeds! You can buy some from the shop.";
                  std::cout << "\n";
                }
                break;
              case 4:
                if (inventory.get_strawberrySeedsCount() > 0) {
                  player->seedPlant(4, &background);
                  inventory.subtractStrawberrySeedsCount();
                } else {
                  std::cout
                      << "No strawberry seeds! You can buy some from the shop.";
                  std::cout << "\n";
                }
                break;
              case 6:
                if (inventory.get_potatoSeedsCount() > 0) {
                  player->seedPlant(6, &background);
                  inventory.subtractPotatoSeedsCount();
                } else {
                  std::cout
                      << "No potato seeds! You can buy some from the shop.";
                  std::cout << "\n";
                }
                break;
              case 8:
                if (inventory.get_carrotSeedsCount() > 0) {
                  player->seedPlant(8, &background);
                  inventory.subtractCarrotSeedsCount();
                } else {
                  std::cout
                      << "No carrot seeds! You can buy some from the shop.";
                  std::cout << "\n";
                }
                break;
            }
          }
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            player->waterPlant(&background);
            std::cout << "watered plant" << std::endl;

            int playerX = (floor(player->get_x() / 50) * 50);
            int playerY = (floor(player->get_y() / 50) * 50);
          }
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Num0)) {
            day.daySkip(&background);
          }
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (menu.get_visibility() == true) {
              menu.moveUp();
            }
            if (buymenu.get_buyOn() == true) {
              buymenu.moveUp();
              buymenu.set_successCheck(false);  // visibility remove
              buymenu.set_failureCheck(false);
            }

            if (sellmenu.get_sellOn() == true) {
              sellmenu.moveUp();
              sellmenu.set_successCheck(false);
              sellmenu.set_successCheck(false);
            }
          }
          if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (menu.get_visibility() == true) {
              menu.moveDown();
            }
            if (buymenu.get_buyOn() == true) {
              buymenu.moveDown();
              buymenu.set_successCheck(false);  // visibility remove
              buymenu.set_failureCheck(false);
            }

            if (sellmenu.get_sellOn() == true) {
              sellmenu.moveDown();
              sellmenu.set_successCheck(false);
              sellmenu.set_successCheck(false);
            }
          }

          if (Keyboard::isKeyPressed(Keyboard::Space)) {
            inventory.scrollInventory();
          }

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (menu.get_visibility() == true)) {
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
              (buymenu.get_buyOn() == true)) {
            // opening the rectangles of the options
            int itemNo = buymenu.get_buySelect();
            switch (itemNo) {
              case 0:
                if (buymenu.purchaseStatus(player, 0) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
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

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (sellmenu.get_sellOn() == true)) {
            // opening the rectangles of the options
            int itemNoSell = sellmenu.get_sellSelect();
            switch (itemNoSell) {
              case 0:
                if (sellmenu.purchaseStatus(&inventory, 0) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add100shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";  // next up, add items into the player's
                                      // inventory
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 1:
                if (sellmenu.purchaseStatus(&inventory, 1) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add80shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";  // next up, add items into the player's
                                      // inventory
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 2:
                if (sellmenu.purchaseStatus(&inventory, 2) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add200shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";  // next up, add items into the player's
                                      // inventory
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 3:
                if (sellmenu.purchaseStatus(&inventory, 3) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add120shells();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";  // next up, add items into the player's
                                      // inventory
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              default:
                std::cout << "Error in selling." << std::endl;
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

      if (Keyboard::isKeyPressed(Keyboard::B) &&
          (menu.get_visibility() == false) &&
          (sellmenu.get_sellOn() == false)) {
        visibleBuy = true;
        buymenu.set_buyOn(visibleBuy);
      }

      if (Keyboard::isKeyPressed(Keyboard::N) &&
          (buymenu.get_buyOn() == false) && (menu.get_visibility() == false)) {
        visibleSell = true;
        sellmenu.set_sellOn(true);
      }

      if (Keyboard::isKeyPressed(Keyboard::M) &&
          (buymenu.get_buyOn() == false) && (sellmenu.get_sellOn() == false)) {
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

      // visibility of menus
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        if (buymenu.get_buyOn() == false && sellmenu.get_sellOn() == false) {
          menu.set_controlVisi(false);
          menu.set_htpVisi(false);
          menu.set_saveVisi(false);

        } else {
          visibleBuy = false;
          buymenu.set_failureCheck(false);
          buymenu.set_successCheck(false);
          buymenu.set_buyOn(false);

          visibleSell = false;
          sellmenu.set_failureCheck(false);
          sellmenu.set_successCheck(false);
          sellmenu.set_sellOn(false);

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
      if (sellmenu.get_sellOn() == true) {
        sellmenu.draw(win);
      }

      // drawing purchase success or failure
      if (buymenu.get_failureCheck() == true) {
        buymenu.drawPurchaseError(win);
      }
      if (buymenu.get_successCheck() == true) {
        buymenu.drawPurchaseSuccess(win);
      }
      // drawing selling success or failure
      if (sellmenu.get_failureCheck() == true) {
        sellmenu.drawSellFailure(win);
      }
      if (sellmenu.get_successCheck() == true) {
        sellmenu.drawSellSuccess(win);
      }

      // drawing the clock
      day.drawDayDracker(win);
      day.dayCountdown(&background);

      inventory.drawInventory(win);
      inventory.drawCounter(win);

      win->display();
    }
    return;
  };

  // getter
  std::vector<tile*> get_background() { return background; }

  ~EverythingDriver(){};
};

int main() {
  EverythingDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}