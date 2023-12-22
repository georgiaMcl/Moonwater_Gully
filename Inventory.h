#ifndef INVENTORY_H
#define INVENTORY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "InventoryItems.h"
using namespace sf;

class Inventory {
 protected:
  std::vector<int> inventory;
  std::vector<InventoryItems*> hotBar;
  RectangleShape* selection;
  Texture selectionTexture;
  int length, width;
  int x, y;
  int inventorySize;
  bool visible;
  Font font;
  Text inventoryName[10];
  Texture hotBarTexture;
  int inventoryIndex;
  std::vector<String> itemCounter;  // string
  Text itemText[10];

 public:
  Inventory(int len, int wid) {
    x = 25;
    y = 500;
    length = len;  // 550
    width = wid;   // 50

    visible = true;

    itemCounter.resize(10);

    for (int i = 0; i < 10; i++) {
      InventoryItems* item = new InventoryItems((i * 55) + 25, 500, i);
      hotBar.push_back(item);
    }

    selectionTexture.loadFromFile("textures/selection.png");
    if (!selectionTexture.loadFromFile("textures/selection.png")) {
      std::cout << "error loading texture" << std::endl;  // error testing
    }
    selection = new RectangleShape(Vector2f(65, 65));
    selection->setTexture(&selectionTexture);
    selection->setTextureRect(IntRect(0, 0, 65, 65));
    selection->setPosition(x - 5, y - 5);

    inventorySize = 10;
    inventoryIndex = 0;

    // loading font
    font.loadFromFile("textures/font_texture/TTF/dogica.ttf");
    if (!font.loadFromFile("textures/font_texture/TTF/dogica.ttf")) {
      std::cout << "error loading font" << std::endl;  // error testing
    }

    inventoryName[0].setFont(font);
    inventoryName[0].setString("shovel");
    inventoryName[0].setCharacterSize(6);
    inventoryName[0].setFillColor(Color::White);
    inventoryName[0].setPosition(30, y + 45);

    inventoryName[1].setFont(font);
    inventoryName[1].setString("glove");
    inventoryName[1].setCharacterSize(6);
    inventoryName[1].setFillColor(Color::White);
    inventoryName[1].setPosition(85, y + 45);

    inventoryName[2].setFont(font);
    inventoryName[2].setString("blueberry seeds");
    inventoryName[2].setCharacterSize(6);
    inventoryName[2].setFillColor(Color::White);
    inventoryName[2].setPosition(135, y - 5);

    inventoryName[3].setFont(font);
    inventoryName[3].setString("blueberries");
    inventoryName[3].setCharacterSize(6);
    inventoryName[3].setFillColor(Color::White);
    inventoryName[3].setPosition(185, y + 45);

    inventoryName[4].setFont(font);
    inventoryName[4].setString("strawberry seeds");
    inventoryName[4].setCharacterSize(6);
    inventoryName[4].setFillColor(Color::White);
    inventoryName[4].setPosition(235, y + 45);

    inventoryName[5].setFont(font);
    inventoryName[5].setString("strawberries");
    inventoryName[5].setCharacterSize(6);
    inventoryName[5].setFillColor(Color::White);
    inventoryName[5].setPosition(285, y + 45);

    inventoryName[6].setFont(font);
    inventoryName[6].setString("potato seeds");
    inventoryName[6].setCharacterSize(6);
    inventoryName[6].setFillColor(Color::White);
    inventoryName[6].setPosition(335, y + 45);

    inventoryName[7].setFont(font);
    inventoryName[7].setString("potato");
    inventoryName[7].setCharacterSize(6);
    inventoryName[7].setFillColor(Color::White);
    inventoryName[7].setPosition(385, y + 45);

    inventoryName[8].setFont(font);
    inventoryName[8].setString("carrot seeds");
    inventoryName[8].setCharacterSize(6);
    inventoryName[8].setFillColor(Color::White);
    inventoryName[8].setPosition(435, y + 45);

    inventoryName[9].setFont(font);
    inventoryName[9].setString("carrot");
    inventoryName[9].setCharacterSize(6);
    inventoryName[9].setFillColor(Color::White);
    inventoryName[9].setPosition(485, y + 45);

    inventory = std::vector<int>(inventorySize,
                                 0);  // initialising inventory values as 0

    inventoryName[inventoryIndex].setFillColor(Color::Green);
  }

  void scrollInventory() {
    // using space bar
    if (inventoryIndex + 1 <= inventorySize) {
      inventoryName[inventoryIndex].setFillColor(Color::White);
      selection->setPosition(x + ((inventoryIndex + 1) * 55) - 5, y - 5);
      // iterating through array
      inventoryIndex++;
      if (inventoryIndex > inventorySize - 1) {
        inventoryIndex = 0;
        selection->setPosition(x - 5, y - 5);
      }

      if (inventoryIndex == 0) {
        inventoryName[inventoryIndex].setFillColor(Color::Green);
      }
      inventoryName[inventoryIndex].setFillColor(Color::Green);
    }
    return;
  }

  void drawInventory(RenderWindow* win) {
    for (auto itemPtr : hotBar) {
      itemPtr->drawInventoryItems(win);
    }
    win->draw(*selection);
    return;
  }

  void drawCounter(RenderWindow* win) {
    for (int i = 0; i < 10; i++) {
      itemCounter[i] = std::to_string(inventory[i]);
      itemText[i].setFont(font);
      itemText[i].setString(itemCounter[i]);
      itemText[i].setCharacterSize(10);
      itemText[i].setFillColor(Color::White);
      itemText[i].setPosition(
          x + (i * 55), y - 5);  // Adjust the position based on the item index

      win->draw(itemText[i]);
    }
    return;
  }

  // getters and setters
  std::vector<int> get_inventory() { return inventory; }
  void set_inventory(std::vector<int> invent) {
    inventory = invent;
    return;
  }
  int get_inventorySize() { return inventorySize; }
  int get_inventoryIndex() { return inventoryIndex; }
  void set_inventoryIndex(int ind) {
    inventoryIndex = ind;
    return;
  }

  void set_visibility(bool visible) {
    this->visible = visible;
    return;
  }
  bool get_visibility() { return visible; }

  int get_shovelCount() { return inventory[0]; }
  int get_gloveCount() { return inventory[1]; }
  int get_blueberrySeedsCount() { return inventory[2]; }
  int get_blueberryCount() { return inventory[3]; }
  int get_strawberrySeedsCount() { return inventory[4]; }
  int get_strawberryCount() { return inventory[5]; }
  int get_potatoSeedsCount() { return inventory[6]; }
  int get_potatoCount() { return inventory[7]; }
  int get_carrotSeedsCount() { return inventory[8]; }
  int get_carrotCount() { return inventory[9]; }
  int get_fromPos(int plantPos) { return inventory[plantPos]; }

  void set_inventoryItemAt(int i, int itemNumber) { inventory[i] = itemNumber; }

  void set_shovelCount(int shovel) {
    inventory[0] = shovel;
    return;
  }
  void set_gloveCount(int glove) {
    inventory[1] = glove;
    return;
  }
  void set_blueberrySeedsCount(int blue_seeds) {
    inventory[2] = blue_seeds;
    return;
  }
  void set_blueberryCount(int blue) {
    inventory[3] = blue;
    return;
  }
  void set_strawberrySeedsCount(int straw_seeds) {
    inventory[4] = straw_seeds;
    return;
  }
  void set_strawberryCount(int straw) {
    inventory[5] = straw;
    return;
  }
  void set_potatoSeedsCount(int potato_seed) {
    inventory[6] = potato_seed;
    return;
  }
  void set_potatoCount(int potato) {
    inventory[7] = potato;
    return;
  }
  void set_carrotSeedsCount(int carrot_seed) {
    inventory[8] = carrot_seed;
    return;
  }
  void set_carrotCount(int carrot) {
    inventory[9] = carrot;
    return;
  }
  void set_fromPos(int plantPos, int amount) {
    inventory[plantPos] = amount;
    return;
  }

  void addShovelCount() {
    inventory[0] += 1;
    return;
  }
  void addGloveCount() {
    inventory[1] += 1;
    return;
  }
  void addBlueberrySeedsCount() {
    inventory[2] += 1;
    return;
  }
  void addBlueberryCount() {
    inventory[3] += 1;
    return;
  }
  void addStrawberrySeedsCount() {
    inventory[4] += 1;
    return;
  }
  void addstrawberryCount() {
    inventory[5] += 1;
    return;
  }
  void addPotatoSeedsCount() {
    inventory[6] += 1;
    return;
  }
  void addPotatoCount() {
    inventory[7] += 1;
    return;
  }
  void addCarrotSeedsCount() {
    inventory[8] += 1;
    return;
  }
  void addCarrotCount() {
    inventory[9] += 1;
    return;
  }

  void subtractShovelCount() {
    inventory[0] -= 1;
    return;
  }
  void subtractGloveCount() {
    inventory[1] -= 1;
    return;
  }
  void subtractBlueberrySeedsCount() {
    inventory[2] -= 1;
    return;
  }
  void subtractBlueberryCount() {
    inventory[3] -= 1;
    return;
  }
  void subtractStrawberrySeedsCount() {
    inventory[4] -= 1;
    return;
  }
  void subtractStrawberryCount() {
    inventory[5] -= 1;
    return;
  }
  void subtractPotatoSeedsCount() {
    inventory[6] -= 1;
    return;
  }
  void subtractPotatoCount() {
    inventory[7] -= 1;
    return;
  }
  void subtractCarrotSeedsCount() {
    inventory[8] -= 1;
    return;
  }
  void subtractCarrotCount() {
    inventory[9] -= 1;
    return;
  }

  ~Inventory() {
    for (InventoryItems* item : hotBar) {
      delete item;
    }
    delete selection;
  }
};

#endif