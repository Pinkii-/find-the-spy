#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include <SFML/Graphics.hpp>

class Input {
public:
  void update(sf::RenderWindow& window) {
#ifdef __linux__
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
#else
    sf::Vector2i localPosition = sf::Touch::getPosition(0, window);
#endif
    pos.x = localPosition.x;
    pos.y = localPosition.y;
    isClick_before = isClick;
#ifdef __linux__
    isClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
#else
    isClick = sf::Touch::isDown(0);
#endif
    isClick_thisframe = isClick && !isClick_before;
  }

  static sf::Vector2i pos;
  static bool isClick_before;
  static bool isClick;
  static bool isClick_thisframe;
};

#endif
