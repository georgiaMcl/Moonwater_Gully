#ifndef DAY_H
#define DAY_H
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

#include "tile.h"
using namespace sf;

class Day {
 protected:
  int dayCount;
  int timeInSec;  // it will start at 180 and count down to 0
  std::string dayCountString;
  std::string timeInSecString;

  std::time_t gameStartTime;
  std::time_t newDayTime;
  std::time_t oneSecond;

  int x, y;
  bool visible;

  Font font;
  Text timeLeftWord;
  Text currentDayWord;
  Text timeLeftValue;
  Text currentDayValue;
  Texture dayTexture;

  // rectangle shape for clock size
  RectangleShape* dayClockBg;

 public:
  Day() {
    dayCount = 0;
    timeInSec = 180;
    gameStartTime = time(NULL);
    newDayTime = time(NULL);
    oneSecond = time(NULL);

    dayCountString = std::to_string(dayCount);
    timeInSecString = std::to_string(timeInSec);

    x = 410;
    y = 25;

    // clock image
    dayClockBg = new RectangleShape(Vector2f(165, 50));
    dayClockBg->setFillColor(Color::White);
    dayClockBg->setPosition(x, y);

    // loading in textures:
    dayTexture.loadFromFile("textures/clock_bg.png");
    dayClockBg->setTexture(&dayTexture);

    dayClockBg->setTextureRect(IntRect(0, 0, 165, 50));

    // loading font
    font.loadFromFile("textures/font_texture/TTF/dogica.ttf");
    if (!font.loadFromFile("textures/font_texture/TTF/dogica.ttf")) {
      std::cout << "error loading font" << std::endl;  // error testing
    }

    // buidling the text in clock box
    timeLeftWord.setFont(font);
    timeLeftWord.setString("Time left: ");
    timeLeftWord.setCharacterSize(10);
    timeLeftWord.setFillColor(Color::Black);
    timeLeftWord.setPosition(x + 15, y + 10);

    timeLeftValue.setFont(font);
    timeLeftValue.setString(timeInSecString);
    timeLeftValue.setCharacterSize(10);
    timeLeftValue.setFillColor(Color::Black);
    timeLeftValue.setPosition(x + 125, y + 10);

    currentDayWord.setFont(font);
    currentDayWord.setString("Day ");
    currentDayWord.setCharacterSize(10);
    currentDayWord.setFillColor(Color::Black);
    currentDayWord.setPosition(x + 15, y + 25);

    currentDayValue.setFont(font);
    currentDayValue.setString(dayCountString);
    currentDayValue.setCharacterSize(10);
    currentDayValue.setFillColor(Color::Black);
    currentDayValue.setPosition(x + 65, y + 25);
  };

  void dayCountdown(std::vector<tile*>* background) {
    // dayCountdown will countdown and change the displayed time every second
    // and changes the displayed day and plant growth once 3 minutes (a full
    // day) has passed. It akes in a vector pointer containing tile pointers and
    // returns nothing but changes object parameters.

    // Check if 3 mins has passed
    if (timeInSec > 0) {
      // updating time to countdown every second
      if ((time(NULL) - oneSecond) == 1) {
        timeInSec--;
        timeInSecString = std::to_string(timeInSec);
        oneSecond = time(NULL);
      }
    }
    // 3 mins has passed and new day begins
    else {
      timeInSec = 180;
      newDayTime = time(NULL);
      oneSecond = time(NULL);
      dayCount++;
      dayCountString = std::to_string(dayCount);

      // makes all the plants grow at the beginning of each day
      for (int i = 0; i < 144; i++) {
        (*background)[i]->newDayGrowth();
        (*background)[i]->grow();

        // killing plant if required
        if ((*background)[i]->get_hydrationLevel() < 0) {
          tile* farmland =
              new tile((*background)[i]->get_x(), (*background)[i]->get_y());
          delete (*background)[i];
          (*background)[i] = farmland;
        }
      }
    }
    return;
  };

  void drawDayDracker(RenderWindow* win) {
    // drawDayDracker will draw the window of the countdown timer in the window.
    //  It takes in a RenderWindow pointer to the background.
    timeLeftWord.setFont(font);
    timeLeftWord.setString("Time left: ");
    timeLeftWord.setCharacterSize(10);
    timeLeftWord.setFillColor(Color::Black);
    timeLeftWord.setPosition(x + 15, y + 10);

    timeLeftValue.setFont(font);
    timeLeftValue.setString(timeInSecString);
    timeLeftValue.setCharacterSize(10);
    timeLeftValue.setFillColor(Color::Black);
    timeLeftValue.setPosition(x + 125, y + 10);

    currentDayWord.setFont(font);
    currentDayWord.setString("Day ");
    currentDayWord.setCharacterSize(10);
    currentDayWord.setFillColor(Color::Black);
    currentDayWord.setPosition(x + 15, y + 25);

    currentDayValue.setFont(font);
    currentDayValue.setString(dayCountString);
    currentDayValue.setCharacterSize(10);
    currentDayValue.setFillColor(Color::Black);
    currentDayValue.setPosition(x + 65, y + 25);

    win->draw(*dayClockBg);
    win->draw(timeLeftWord);
    win->draw(currentDayWord);
    win->draw(timeLeftValue);
    win->draw(currentDayValue);

    return;
  };

  void daySkip(std::vector<tile*>* background) {
    // daySkip will start a new day, changing the day values and plant object
    // parameters to reflect a new day. It takes in a vector pointer of tile
    // pointers and will return nothing.
    timeInSec = 180;
    newDayTime = time(NULL);
    oneSecond = time(NULL);
    dayCount++;
    dayCountString = std::to_string(dayCount);

    // makes all the plants grow at the beginning of each day
    for (int i = 0; i < 144; i++) {
      (*background)[i]->newDayGrowth();
      (*background)[i]->grow();

      // killing plant if required
      if ((*background)[i]->get_hydrationLevel() < 0) {
        tile* farmland =
            new tile((*background)[i]->get_x(), (*background)[i]->get_y());
        delete (*background)[i];
        (*background)[i] = farmland;
      }
    }
    std::cout << "day has been skipped" << std::endl;
    return;
  }

  // the getters and setters
  int get_dayCount() { return dayCount; };
  void set_dayCount(int dayCount) {
    this->dayCount = dayCount;
    return;
  };

  time_t get_gameStartTime() { return gameStartTime; };
  void set_gameStartTime(time_t gameStartTime) {
    this->gameStartTime = gameStartTime;
    return;
  };

  time_t get_newDayTime() { return newDayTime; };
  void set_newDayTime(time_t newDayTime) {
    this->newDayTime = newDayTime;
    return;
  };

  time_t get_oneSecond() { return oneSecond; };
  void set_oneSecond(time_t oneSecond) {
    this->oneSecond = oneSecond;
    return;
  };

  std::string get_dayCountString() { return dayCountString; };
  void set_dayCountString(std::string dayCountString) {
    this->dayCountString = dayCountString;
    return;
  };

  std::string get_timeInSecString() { return timeInSecString; };
  void set_timeInSecString(std::string timeInSecString) {
    this->timeInSecString = timeInSecString;
    return;
  };

  int get_timeInSec() { return timeInSec; };
  void set_timeInSec(int timeInSec) {
    this->timeInSec = timeInSec;
    return;
  };

  int get_x() { return x; };
  void set_x(int x) {
    this->x = x;
    return;
  };

  int get_y() { return y; };
  void set_y(int y) {
    this->y = y;
    return;
  };

  Font get_font() { return font; };
  void set_font(Font font) {
    this->font = font;
    return;
  };

  Text get_timeLeftWord() { return timeLeftWord; };
  void set_timeLeftWord(Text timeLeftWord) {
    this->timeLeftWord = timeLeftWord;
    return;
  };

  Text get_currentDayWord() { return currentDayWord; };
  void set_currentDayWord(Text currentDayWord) {
    this->currentDayWord = currentDayWord;
    return;
  };

  Text get_timeLeftValue() { return timeLeftValue; };
  void set_timeLeftValue(Text timeLeftValue) {
    this->timeLeftValue = timeLeftValue;
    return;
  };

  Text get_currentDayValue() { return currentDayValue; };
  void set_currentDayValue(Text currentDayValue) {
    this->currentDayValue = currentDayValue;
    return;
  };

  Texture get_dayTexture() { return dayTexture; };
  void set_dayTexture(Texture dayTexture) {
    this->dayTexture = dayTexture;
    return;
  };

  RectangleShape* get_dayClockBg() { return dayClockBg; };
  void set_dayClockBg(RectangleShape* dayClockBg) {
    this->dayClockBg = dayClockBg;
    return;
  };

  void set_visibility(bool visible) { this->visible = visible; }
  bool get_visibility() { return visible; }

  ~Day(){};
};

#endif