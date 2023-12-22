#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#include "Blueberry.h"
#include "BuyMenu.h"
#include "Carrot.h"
#include "Day.h"
#include "Inventory.h"
#include "Menu.h"
#include "Player.h"
#include "Potato.h"
#include "SaveGame.h"
#include "SellMenu.h"
#include "Strawberry.h"
#include "tile.h"

class Game {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Player* player;
  Menu menu = Menu(300, 150);
  BuyMenu buymenu = BuyMenu(250, 400);
  SellMenu sellmenu = SellMenu(250, 300);
  Inventory inventory = Inventory(550, 55);
  Day day;
  SaveGame saver = SaveGame(300, 150);
  bool visibleMenu = true;
  bool visibleBuy = false;
  bool visibleSell = false;
  bool visibleInventory = true;

  bool onKeyHold = false;

 public:
  Game(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    player = new Player(10, 50, 50);
    visibleBuy = false;
    visibleMenu = false;
    visibleSell = false;
    visibleInventory = true;
  };

  void makeBackground() {
    // Creates game tile background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
  };

  void run() {
    // Runs the game
    while (win->isOpen()) {
      Event e;

      sf::Clock clock;
      const sf::Time targetFrameTime = sf::seconds(1.0f / 100.0f);

      while (win->pollEvent(e)) {
        if (e.type == Event::Closed) {
          win->close();
        }

        // iterating space
        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Space) &&
              (saver.get_loadVisibility() == false)) {
            inventory.scrollInventory();
          } else if ((Keyboard::isKeyPressed(Keyboard::Space)) &&
                     (saver.get_loadVisibility() == true)) {
            saver.scrollLoad();
          }

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (sellmenu.get_sellOn() == false) &&
              (buymenu.get_buyOn() == false) &&
              (menu.get_visibility() == false) &&
              (saver.get_loadVisibility() == true)) {
            int select = saver.get_select();
            switch (select) {
              case 0:
                saver.load(background, &inventory, player, &day);
                // create pop up
                saver.set_loadVisibility(false);
                menu.set_visibility(true);
                break;
              case 1:
                saver.clearFile();
                saver.set_loadVisibility(false);
                menu.set_visibility(true);
                break;
            }
            break;
          }
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::P)) {
            // Planting seeds
            if (background[player->get_x() / 50 * 12 + player->get_y() / 50]
                    ->get_isPlantable() == true) {
              switch (inventory.get_inventoryIndex()) {
                case 2:  // Blueberry seeds
                  if (inventory.get_blueberrySeedsCount() > 0) {
                    player->seedPlant(2, &background);
                    inventory.subtractBlueberrySeedsCount();
                  } else {
                    std::cout << "No blueberry seeds! You can buy some from "
                                 "the shop.";
                    std::cout << "\n";
                  }
                  break;
                case 4:  // Strawberry seeds
                  if (inventory.get_strawberrySeedsCount() > 0) {
                    player->seedPlant(4, &background);
                    inventory.subtractStrawberrySeedsCount();
                  } else {
                    std::cout << "No strawberry seeds! You can buy some from "
                                 "the shop.";
                    std::cout << "\n";
                  }
                  break;
                case 6:  // Potato seeds
                  if (inventory.get_potatoSeedsCount() > 0) {
                    player->seedPlant(6, &background);
                    inventory.subtractPotatoSeedsCount();
                  } else {
                    std::cout
                        << "No potato seeds! You can buy some from the shop.";
                    std::cout << "\n";
                  }
                  break;
                case 8:  // Carrot seeds
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
        }

        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            // Watering tiles
            player->waterPlant(&background);
            std::cout << "watered plant" << std::endl;

            // int playerX = (floor(player->get_x() / 50) * 50);
            // int playerY = (floor(player->get_y() / 50) * 50);
          }
        }

        if (e.type == Event::KeyPressed) {
          // Harvesting plants
          if (Keyboard::isKeyPressed(Keyboard::H)) {
            std::cout << "Harvested Plant" << std::endl;
            player->harvestPlant(&background, &inventory);
          }
        }

        if (e.type == Event::KeyPressed) {
          // Skipping ahead by 1 day
          if (Keyboard::isKeyPressed(Keyboard::Num0)) {
            if (!onKeyHold) {
              day.daySkip(&background);
            }
            onKeyHold = true;
          }
        }

        else if (e.type == Event::KeyReleased) {
          if (e.key.code == Keyboard::Num0) {
            onKeyHold = false;
          }
        }

        if (e.type == Event::KeyPressed) {
          // Navigating menus
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

          // // scrolling through save options
          // if ((Keyboard::isKeyPressed(Keyboard::Space)) &&
          //     (menu.get_saveVisi() == true)) {
          //   menu.scrollSave();
          // }

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (menu.get_visibility() == true) &&
              (buymenu.get_buyOn() == false) &&
              (sellmenu.get_sellOn() == false) &&
              (saver.get_loadVisibility() == false)) {
            // opening the rectangles of the options
            int selection = menu.menuPressed();
            switch (selection) {
              case 0:
                // close the menu and access game window
                visibleMenu = false;
                menu.set_visibility(visibleMenu);
                inventory.set_visibility(true);
                break;
              case 1:
                // open game description
                menu.set_visibility(false);
                menu.set_htpVisi(true);
                inventory.set_visibility(false);
                break;
              case 2:
                // open controls rectangle
                menu.set_visibility(false);
                menu.set_controlVisi(true);
                inventory.set_visibility(true);
                break;
              case 3:
                // open save confirmation
                menu.set_visibility(false);
                menu.set_saveVisi(true);
                inventory.set_visibility(false);
                break;
            }
          }

          if ((menu.get_saveVisi() == true) && (buymenu.get_buyOn() == false) &&
              (menu.get_visibility() == false) &&
              (sellmenu.get_sellOn() == false) &&
              (Keyboard::isKeyPressed(Keyboard::Return))) {
            int saveSelect = menu.get_saveSelect();
            menu.set_saveSuccess(false);
            menu.set_saveSelect(0);
            switch (saveSelect) {
              case 0:
                saver.save(background, 144, &inventory, player,
                           &day);  // saving game into save.txt
                                   // otherwise, exiting
                if (saver.get_saveCheck() == true) {
                  menu.set_saveSuccess(true);
                  menu.set_saveFail(false);
                }
                break;
              case 1:
                if (saver.get_saveCheck() == false) {
                  menu.set_saveSuccess(false);
                }
                menu.set_visibility(false);  // otherwise, exiting
                menu.set_saveVisi(false);

                break;
            }
          }

          if (Keyboard::isKeyPressed(Keyboard::Return) &&
              (buymenu.get_buyOn() == true) &&
              (menu.get_visibility() == false) &&
              (sellmenu.get_sellOn() == false)) {
            // opening the rectangles of the options
            int itemNo = buymenu.get_buySelect();
            switch (itemNo) {
              case 0:  // Purchasing carrot seeds
                if (buymenu.purchaseStatus(player, 0) == true) {
                  buymenu.set_successCheck(true);
                  buymenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";
                  inventory.addCarrotSeedsCount();
                  std::cout << "Carrot seeds in inventory: "
                            << inventory.get_carrotSeedsCount() << std::endl;
                } else {
                  buymenu.set_successCheck(false);
                  buymenu.set_failureCheck(true);
                }
                break;
              case 1:  // Purchasing potato seeeds
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
              case 2:  // Purchasing strawberry seeds
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
              case 3:  // Purchasing blueberry seeds
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
              case 4:  // Purchasing shovel
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
              case 5:  // Purchasing gloves
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
              (sellmenu.get_sellOn() == true) &&
              (buymenu.get_buyOn() == false) &&
              (menu.get_visibility() == false) &&
              (saver.get_loadVisibility() == false)) {
            // opening the rectangles of the options
            int itemNoSell = sellmenu.get_sellSelect();
            switch (itemNoSell) {
              case 0:  // Selling carrot
                if (sellmenu.purchaseStatus(&inventory, 0) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add100shells();
                  inventory.subtractCarrotCount();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 1:  // Selling potato
                if (sellmenu.purchaseStatus(&inventory, 1) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add80shells();
                  inventory.subtractPotatoCount();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 2:  // Selling strawberry
                if (sellmenu.purchaseStatus(&inventory, 2) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add200shells();
                  inventory.subtractStrawberryCount();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";
                } else {
                  sellmenu.set_successCheck(false);
                  sellmenu.set_failureCheck(true);
                }
                break;
              case 3:  // Selling Blueberry
                if (sellmenu.purchaseStatus(&inventory, 3) == true) {
                  sellmenu.set_successCheck(true);
                  sellmenu.set_failureCheck(false);

                  std::cout << "Shells: " << player->get_shells();
                  std::cout << "\n";
                  player->add120shells();
                  inventory.subtractBlueberryCount();
                  std::cout << "Remaining shells: " << player->get_shells();
                  std::cout << "\n";
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

      // Player movement
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

      // Testing of keyboard for menu toggling
      if (Keyboard::isKeyPressed(Keyboard::B) &&
          (menu.get_visibility() == false) && (menu.get_htpVisi() == false) &&
          (menu.get_saveVisi() == false) && (menu.get_controlVisi() == false) &&
          (sellmenu.get_sellOn() == false) &&
          (saver.get_loadVisibility() == false)) {
        visibleBuy = true;
        menu.set_walletVisibility(true);
        buymenu.set_buyOn(visibleBuy);
      }

      if (Keyboard::isKeyPressed(Keyboard::N) &&
          (buymenu.get_buyOn() == false) && (menu.get_visibility() == false) &&
          (menu.get_htpVisi() == false) && (menu.get_saveVisi() == false) &&
          (menu.get_controlVisi() == false) &&
          (saver.get_loadVisibility() == false)) {
        visibleSell = true;
        menu.set_walletVisibility(true);
        sellmenu.set_sellOn(true);
      }

      if (Keyboard::isKeyPressed(Keyboard::M) &&
          (buymenu.get_buyOn() == false) && (sellmenu.get_sellOn() == false)) {
        if ((menu.get_controlVisi() == false) &&
            (menu.get_htpVisi() == false) && (menu.get_saveVisi() == false) &&
            (saver.get_loadVisibility() == false)) {
          visibleMenu = true;
          menu.set_visibility(visibleMenu);
        }
      }

      // Drawing the background tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      }

      // Visibility of menus
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        inventory.set_visibility(true);
        if (buymenu.get_buyOn() == false && sellmenu.get_sellOn() == false) {
          menu.set_controlVisi(false);
          menu.set_htpVisi(false);
          menu.set_saveVisi(false);
          menu.set_saveSuccess(false);
          menu.set_saveFail(false);

        } else {
          menu.set_walletVisibility(false);
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

      // Drawing the menus
      if (menu.get_visibility() == true) {
        menu.draw(win);
      }
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
      if (menu.get_walletVisibility() == true) {
        menu.drawWallet(win, player);
      }
      if (saver.get_loadVisibility() == true) {
        saver.drawLoad(win);
      }

      // Drawing purchase success or failure
      if (buymenu.get_failureCheck() == true) {
        buymenu.drawPurchaseError(win);
      }
      if (buymenu.get_successCheck() == true) {
        buymenu.drawPurchaseSuccess(win);
      }
      // Drawing selling success or failure
      if (sellmenu.get_failureCheck() == true) {
        sellmenu.drawSellFailure(win);
      }
      if (sellmenu.get_successCheck() == true) {
        sellmenu.drawSellSuccess(win);
      }

      if (menu.get_saveSuccess() == true && menu.get_visibility() == false) {
        menu.drawSuccess(win);
      }
      if (menu.get_saveFail() == true && menu.get_visibility() == false) {
        menu.drawFail(win);
      }

      // Drawing the clock
      day.drawDayDracker(win);
      day.dayCountdown(&background);

      if (inventory.get_visibility() == true) {
        inventory.drawInventory(win);
        inventory.drawCounter(win);
      }

      win->display();

      sf::Time elapsed = clock.getElapsedTime();
      if (elapsed < targetFrameTime) {
        sf::sleep(targetFrameTime - elapsed);
      }
      clock.restart();
    }
    return;
  };

  // Getter
  std::vector<tile*> get_background() { return background; }
};

#endif
