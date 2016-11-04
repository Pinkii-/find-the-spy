#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include <SFML/Graphics.hpp>

class Input {
public:
  void update(sf::RenderWindow& window) {
#ifdef __linux__
    pos = sf::Mouse::getPosition(window);
#else
    pos = sf::Touch::getPosition(0, window);
#endif
    wasClicked = isClicked;
#ifdef __linux__
    isClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
#else
    isClicked = sf::Touch::isDown(0);
#endif
    cryMeARivered = isClicked && !wasClicked;
    hasBeenReleased = !isClicked && wasClicked;
  }

  static sf::Vector2i pos;
  static bool wasClicked;
  static bool isClicked;
  static bool cryMeARivered;
  static bool hasBeenReleased;
};

#endif
