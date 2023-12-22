#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
using namespace sf;

class SaveGame {
 protected:
  std::fstream saveFile;
  RectangleShape* loadAsk;
  Texture loadTexture;
  bool loadAskVisible;
  bool saveCheck;
  int x, y;
  Text confirm[2];
  int selection;
  Font font;

 public:
  // saving game
  SaveGame() {}

  SaveGame(int len, int width) {
    // writing first pop up when game is booted up, takes in length and width of
    // load game menu
    x = 125;
    y = 150;
    selection = 0;

    saveCheck = false;

    // texture loading
    loadTexture.loadFromFile("textures/main_menu.png");

    loadAskVisible = true;
    loadAsk = new RectangleShape(Vector2f(360, 150));

    loadAsk->setTexture(&loadTexture);
    loadAsk->setPosition(x, y);

    // loading font
    font.loadFromFile("textures/font_texture/TTF/dogica.ttf");
    if (!font.loadFromFile("textures/font_texture/TTF/dogica.ttf")) {
      std::cout << "error loading font" << std::endl;  // error testing
    }

    // creating options for text
    confirm[0].setFont(font);
    confirm[0].setString("load last save");
    confirm[0].setCharacterSize(15);
    confirm[0].setFillColor(Color::Black);
    confirm[0].setPosition(x + 25, y + 25);

    confirm[1].setFont(font);
    confirm[1].setString("start new game");
    confirm[1].setCharacterSize(15);
    confirm[1].setFillColor(Color::Black);
    confirm[1].setPosition(x + 25, y + 100);

    confirm[selection].setFillColor(Color::Yellow);  // use to navigate
  }

  void scrollLoad() {
    // Scrolling through the options, similar to inventory, takes in and returns
    // nothing
    if (selection + 1 <= 2) {
      confirm[selection].setFillColor(Color::Black);
      selection++;
      if (selection > 1) {
        selection = 0;
      }
      if (selection == 0) {
        confirm[selection].setFillColor(Color::Yellow);
      }

      confirm[selection].setFillColor(Color::Yellow);
    }
  }

  void drawLoad(RenderWindow* win) {
    // Draws load menu screen, takes in a RenderWindow pointer, returns nothing
    win->draw(*loadAsk);
    for (int i = 0; i < 2; i++) {
      win->draw(confirm[i]);
    }
    return;
  }

  void save(std::vector<tile*>& background, int size, Inventory* inventory,
            Player* player, Day* day) {
    // Creates a txt file containing all game information, takes in a vector of
    // tile pointers, size, an inventory pointer, a player pointer, and a day
    // pointer.
    saveFile.open("save.txt", std::ios::out);
    if (!saveFile.is_open()) {
      std::cout << "file could not be opened for saving." << std::endl;
      return;  // error handling
    } else {
      saveCheck = true;
    }
    // in file when reading through to load, check
    // newTile then get next tile to load info
    // save a vector of tiles
    for (int i = 0; i < size; i++) {
      saveFile << "newTile,";

      saveFile << background[i]->get_className()
               << " ";  // comma used as a deliminator when using get_line()
      // get coordinates
      saveFile << background[i]->get_x() << " ";

      saveFile << background[i]->get_y() << " ";

      saveFile << background[i]->get_growthStage() << " ";

      saveFile << background[i]->get_hydrationLevel() << " ";

      saveFile << background[i]->get_imageDescription() << " ";

      saveFile << "\n";
    }

    // save inventory count of each item
    for (int i = 0; i < (inventory->get_inventorySize()); i++) {
      saveFile << "inventory,";  // in file， check when u see "inventory"
      saveFile << inventory->get_inventory()[i] << " ";
      saveFile << "\n";
    }

    saveFile << "shellNumber,";

    // save player shell number
    saveFile << player->get_shells();

    saveFile << "\n";  // line by line approach

    // save day number

    saveFile << "dayCount,";
    saveFile << day->get_dayCount();
    saveFile << "\n";  // line by line approach

    // save time left in day
    saveFile << "dayTime,";
    saveFile << day->get_timeInSec();
    saveFile << "\n";  // line by line approach

    saveFile.close();

    std::cout << "game saved,";  // if statement to check when to stop
    return;
  };

  void load(std::vector<tile*>& background, Inventory* inventory,
            Player* player, Day* day) {
    // Loads the old game from the txt file, takes in a vector of tile pointers,
    // an inventory pointer, a player pointer, and a day pointer, returns
    // nothing
    std::ifstream saveFile("save.txt");

    if (!saveFile.is_open()) {
      std::cout << "File could not be opened for loading." << std::endl;
      return;  // Error handling
    }

    std::string line;
    // temporary background;
    std::vector<tile*> tempBg;
    // temporary inventory
    std::vector<int> tempInv;

    while (std::getline(saveFile, line)) {
      std::istringstream iss(line);
      std::string token;

      // split line via commas
      while (std::getline(iss, token, ',')) {
        // determine the data type based on the first token
        if (token == "newTile") {
          // reading in tile data
          int x, y, growthStage, hydrationLevel;
          std::string className, imageDescription;

          if (iss >> className >> x >> y >> growthStage >> hydrationLevel >>
              imageDescription) {  // reads via line spaced
            // switch case to add tile to background
            // switch case needed as it adds a different type of tile depending
            // on the save file
            if (className == "tile") {
              tile* newTile = new tile(x, y);  // creates new tile
              newTile->set_hydrationLevel(hydrationLevel);
              newTile->set_texture(imageDescription);

              tempBg.push_back(newTile);

            } else if (className == "Carrot") {
              Carrot* carrotTile = new Carrot(x, y);
              carrotTile->set_hydrationLevel(hydrationLevel);
              carrotTile->set_growthStage(
                  growthStage);  // updates growth stage. needed as plants only
                                 // have growth stage but parent class of tile
                                 // does not
              carrotTile->set_texture(imageDescription);

              std::cout << "carrot created";

              tempBg.push_back(carrotTile);

            } else if (className == "Potato") {
              Potato* potatoTile = new Potato(x, y);
              potatoTile->set_hydrationLevel(hydrationLevel);
              potatoTile->set_growthStage(growthStage);
              potatoTile->set_texture(imageDescription);

              tempBg.push_back(potatoTile);

            } else if (className == "Strawberry") {
              Strawberry* strawberryTile = new Strawberry(x, y);
              strawberryTile->set_hydrationLevel(hydrationLevel);
              strawberryTile->set_growthStage(growthStage);
              strawberryTile->set_texture(imageDescription);

              tempBg.push_back(strawberryTile);

            } else if (className == "Blueberry") {
              Blueberry* blueberryTile = new Blueberry(x, y);
              blueberryTile->set_hydrationLevel(hydrationLevel);
              blueberryTile->set_growthStage(growthStage);
              blueberryTile->set_texture(imageDescription);

              tempBg.push_back(blueberryTile);
            }
          }
        } else if (token == "inventory") {
          // read into inventory
          int item;
          if (iss >> item) {
            // add the item to the inventory
            tempInv.push_back(item);
          }
        } else if (token == "shellNumber") {
          // read player shell number
          int shells;
          if (iss >> shells) {
            player->set_shells(shells);
          }
        } else if (token == "dayCount") {
          // read day count
          int dayCount;
          if (iss >> dayCount) {
            day->set_dayCount(dayCount);
            day->set_dayCountString(std::to_string(
                dayCount));  // reason why it won't work is probably bc there
                             // needs to be a separate function in drawing the
                             // day count?
          }
        } else if (token == "dayTime") {
          // Read day time
          int dayTime;
          if (iss >> dayTime) {
            day->set_timeInSec(dayTime);
          }
        }
      }

      background = tempBg;
      inventory->set_inventory(tempInv);
    }

    saveFile.close();
    std::cout << "Game loaded." << std::endl;
    return;
  }
  // function clears the text file when you want to start a new game with no
  // save
  void clearFile() {
    saveFile.open("save.txt", std::ofstream::out | std::ofstream::trunc);
    saveFile.close();
    std::cout << "cleared successfully" << std::endl;
    return;
  }

  // getters and setters
  bool get_loadVisibility() { return loadAskVisible; }
  void set_loadVisibility(bool visi) { loadAskVisible = visi; }
  int get_select() { return selection; }
  void set_select(int sel) { selection = sel; }

  bool get_saveCheck() { return saveCheck; }
  void set_saveCheck(bool check) { saveCheck = check; }
};
#endif