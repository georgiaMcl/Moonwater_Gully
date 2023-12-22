#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class TextBox {
 protected:
  RectangleShape* textbox;
  Text text;
  float length, width;
  Texture textTexture;
  bool isVisible;

 public:
  TextBox(float len, float wid) {
    length = len;
    width = wid;
    textbox = new RectangleShape(Vector2f(length, width));
    textTexture.loadFromFile("textures/text_box_texture.png");
    textbox->setTexture(&textTexture);
    textbox->setTextureRect(IntRect(0, 0, length, width));
    if (!textTexture.loadFromFile("textures/text_box_texture.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    textbox->setPosition(500, 500);
    isVisible = true;
  };

  void draw(RenderWindow* win) {
    // Draws the textbox in the window when given a RenderWindow pointer,
    // returns nothing
    win->draw(*textbox);
    return;
  };

  // getters and setters
  Text get_text() { return text; }
  bool get_visible() { return isVisible; }
  void set_visible(bool visible) {
    isVisible = visible;
    return;
  }
  void set_text(Text _text) {
    text = _text;
    return;
  }

  ~TextBox() { delete[] textbox; };
};

#endif