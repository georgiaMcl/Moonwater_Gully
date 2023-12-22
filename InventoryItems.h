#ifndef INVENTORYITEMS_H
#define INVENTORYITEMS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;

class InventoryItems {
 protected:
  RectangleShape* item;
  std::string textureName;
  Texture texture;
  int itemNumber;
  int x, y;
  int size;

 public:
  InventoryItems(int _x, int _y, int itemNo) {
    x = _x;
    y = _y;
    size = 55;
    itemNumber = itemNo;
    switch (itemNumber) {
      case 0:
        textureName = "textures/inventoryShovel.png";
        break;
      case 1:
        textureName = "textures/inventoryGloves.png";
        break;
      case 2:
        textureName = "textures/inventoryBlueberrySeeds.png";
        break;
      case 3:
        textureName = "textures/inventoryBlueberry.png";
        break;
      case 4:
        textureName = "textures/inventoryStrawberrySeeds.png";
        break;
      case 5:
        textureName = "textures/inventoryStrawberry.png";
        break;
      case 6:
        textureName = "textures/inventoryPotatoSeeds.png";
        break;
      case 7:
        textureName = "textures/inventoryPotato.png";
        break;
      case 8:
        textureName = "textures/inventoryCarrotSeeds.png";
        break;
      case 9:
        textureName = "textures/inventoryCarrot.png";
        break;
    }
    item = new RectangleShape(Vector2f(size, size));
    texture.loadFromFile(textureName);
    item->setTexture(&texture);
    item->setTextureRect(IntRect(0, 0, size, size));
    if (!texture.loadFromFile(textureName)) {
      std::cout << "Error loading texture" << std::endl;
    }
    item->setPosition(x, y);
  }
  void drawInventoryItems(RenderWindow* win) {
    // Will draw the inventory item iamge in the hotbar after taking in a
    // RenderWindow pointer to the window
    win->draw(*item);
    return;
  }

  ~InventoryItems(){};
};

#endif