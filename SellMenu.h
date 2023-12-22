#ifndef SELLMENU_H
#define SELLMENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Inventory.h"
#include "Menu.h"
#include "Player.h"
using namespace sf;

class SellMenu : public Menu {
 protected:
  RectangleShape* sellBackground;
  RectangleShape* sellBox;
  bool sellOn;  // turning the selling box on
  Text sellCatalogue[4];
  Text sellSuccess[3];  // box displaying
  int sellSelect;       //  selecting the item in the sell menu

  bool successCheck;
  bool failureCheck;

  Texture bgTexture;

 public:
  SellMenu(int len, int wid) : Menu(len, wid) {
    x = 25;
    y = 25;
    length = len;   // 200
    width = wid;    // 300
    maxOption = 4;  // only sell blueberries, strawberries, potatos and carrots

    successCheck = false;
    failureCheck = false;

    // background boxes
    sellBackground = new RectangleShape(Vector2f(length, width + 100));
    sellBackground->setFillColor(Color::White);

    sellBox = new RectangleShape(Vector2f(230, 200));
    sellBox->setFillColor(Color::White);

    // loading in textures:
    bgTexture.loadFromFile("textures/beigeBackground.png");
    sellBackground->setTexture(&bgTexture);
    sellBox->setTexture(&bgTexture);

    // setting the selling menu
    int textX = 35;
    sellCatalogue[0].setFont(font);
    sellCatalogue[0].setString("1x carrot      100");
    sellCatalogue[0].setCharacterSize(10);
    sellCatalogue[0].setFillColor(Color::White);
    sellCatalogue[0].setPosition(textX, 70);

    sellCatalogue[1].setFont(font);
    sellCatalogue[1].setString("1x potato       80");
    sellCatalogue[1].setCharacterSize(10);
    sellCatalogue[1].setFillColor(Color::White);
    sellCatalogue[1].setPosition(textX, 90);

    sellCatalogue[2].setFont(font);
    sellCatalogue[2].setString("1x strawberry   200");
    sellCatalogue[2].setCharacterSize(10);
    sellCatalogue[2].setFillColor(Color::White);
    sellCatalogue[2].setPosition(textX, 110);

    sellCatalogue[3].setFont(font);
    sellCatalogue[3].setString("1x blueberry    120");
    sellCatalogue[3].setCharacterSize(10);
    sellCatalogue[3].setFillColor(Color::White);
    sellCatalogue[3].setPosition(textX, 130);

    sellSelect = 0;

    sellCatalogue[sellSelect].setFillColor(Color::Yellow);

    // creating purchase box list:
    sellSuccess[0].setFont(font);
    sellSuccess[0].setString("sell item?");
    sellSuccess[0].setCharacterSize(10);
    sellSuccess[0].setFillColor(Color::Black);
    sellSuccess[0].setPosition(290, 35 + 200);

    sellSuccess[1].setFont(font);
    sellSuccess[1].setString("Sold!");
    sellSuccess[1].setCharacterSize(10);
    sellSuccess[1].setFillColor(Color::Black);
    sellSuccess[1].setPosition(290, 50 + 260);

    sellSuccess[2].setFont(font);
    sellSuccess[2].setString("You don't have any\n\n"
    "of this item to sell!");
    sellSuccess[2].setCharacterSize(10);
    sellSuccess[2].setFillColor(Color::Black);
    sellSuccess[2].setPosition(290, 50 + 260);


    sellBackground->setPosition(x, y);
    sellBox->setPosition(280, 25 + 200);
    // turning on and off
    sellOn = false;
  }
  void moveDown() {
    // Moves the sellSelect option down if there is an option below, returns nothing.

    // checking array
    if (sellSelect + 1 < maxOption) {
      // changing text colour
      sellCatalogue[sellSelect].setFillColor(sf::Color::White);
      // iterating array
      sellSelect++;
      // changing text colour
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    } else if (sellSelect == 3) {
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    } else { // should technically never implement because it is covered by above statements
      sellSelect = 0;
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    }
    return;
  }
  void moveUp() {
    // Moves the sellSelect option up if there is an option above, returns nothing.

    // checking array
    if (sellSelect - 1 >= 0 && sellSelect < maxOption) {
      sellCatalogue[sellSelect].setFillColor(sf::Color::White);
      sellSelect--;
      // changing text colour
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    } else if (sellSelect == 0) {
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    } else {
      sellSelect = 0;
      sellCatalogue[sellSelect].setFillColor(sf::Color::Yellow);
    }
    return;
  }

  bool purchaseStatus(Inventory* inventory, int itemNo) {
    // Returns a bool value if the purchase the player wishes to make is allowed,
    // takes in a pointer to the inventory, and the itemNo the player wishes to purchase
    switch (itemNo) {
      case 0:  // carrot
        if (inventory->get_carrotCount() >= 1) {
          return true;
        } else {
          return false;
        }
        break;
      case 1:  // potato
        if (inventory->get_potatoCount() >= 1) {
          return true;
        } else {
          return false;
        }
        break;
      case 2:  // strawberry
        if (inventory->get_strawberryCount() >= 1) {
          return true;
        } else {
          return false;
        }
        break;
      case 3:  // blueberry
        if (inventory->get_blueberryCount() >= 1) {
          return true;
        } else {
          return false;
        }
        break;
      default:
        return false;
    }
  }
  void draw(RenderWindow* win) {
    // Draws the sell window in the game window when given a RenderWindow pointer
    win->draw(*sellBackground);
    win->draw(*sellBox);
    for (int i = 0; i < maxOption; i++) {
      win->draw(sellCatalogue[i]);
    }
    win->draw(sellSuccess[0]);
    return;
  }

  void drawSellSuccess(RenderWindow* win) { 
    // Draws the sell success message in the window when given a RenderWindow pointer
    win->draw(sellSuccess[1]);
    return;
  }
  void drawSellFailure(RenderWindow* win) { 
    // Draws the sell failure message in the window when given a RenderWindow pointer
    win->draw(sellSuccess[2]);
    return;
  };

  // setters and getters
  bool get_successCheck() { return successCheck; }
  void set_successCheck(bool su) { 
    successCheck = su;
    return;
  }
  bool get_failureCheck() { return failureCheck; }
  void set_failureCheck(bool fa) { 
    failureCheck = fa;
    return;
  }

  void set_sellSelect(int select) { 
    sellSelect = select;
    return;
  }
  int get_sellSelect() { return sellSelect; }

  void set_maxOption(int max) { 
    maxOption = max;
    return;
  }
  int get_maxOption() { return maxOption; }

  bool get_sellOn() { return sellOn; }
  void set_sellOn(bool visible) { 
    sellOn = visible;
    return;
  }

  ~SellMenu() {
    delete[] sellBackground;
    delete[] sellBox;
  }
};

#endif
