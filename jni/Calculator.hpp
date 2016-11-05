#ifndef __CALCULATOR_HPP__
#define __CALCULATOR_HPP__

#include "Input.hpp"
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include <iostream>

#define SIZEX 66*1.2
#define SIZEY 40*1.2

#define GRAY sf::Color(220,220,220)
#define LIGHTGRAY sf::Color(155,155,155)


//TODO: Hacerlo mas caixa-like
class Calculator : public sf::Drawable, public sf::Transformable {
public:
  Calculator() {
    _passwd.setFont(Resources::font);
    _passwd.setFillColor(sf::Color::Black);
    _passwd.setOutlineColor(sf::Color::White);
    _passwd.setOutlineThickness(1);
    for (int i = 0; i < 10; ++i) {
      _numbers[i].setFont(Resources::font);
      _numbers[i].setString(std::to_string(i+1));
      int x = (i)%3 * SIZEX;
      int y = (i)/3 * SIZEY;
      _numbers[i].setOrigin(16, 22);
      _numbers[i].setPosition(x + SIZEX/2.f, y+SIZEY/2.f + 40);
      _numbers[i].setOutlineColor(sf::Color::Black);
      _numbers[i].setOutlineThickness(3);
      _buttons[i].setPosition(x, y + 40);
      _buttons[i].setSize({SIZEX-(5*2), SIZEY-(5*2)});
      _buttons[i].setFillColor(GRAY);
      _buttons[i].setOutlineThickness(5);
      _buttons[i].setOutlineColor(sf::Color::Black);
    }
    _numbers[9].move(SIZEX, 0);
    _numbers[9].setString("C");
    _buttons[9].move(SIZEX, 0);
  }

  void update(float) {
    for (int i = 0; i < 10; ++i) {
      _buttons[i].setFillColor(GRAY);
      _buttons[i].setOutlineColor(sf::Color::Black);
    }
    if (Input::isClicked || Input::hasBeenReleased) {
      sf::Vector2f localPosition = sf::Vector2f(Input::pos) - getPosition();
      localPosition.x /= getScale().x;
      localPosition.y /= getScale().y;
      if (sf::FloatRect(0,0,SIZEX*3, SIZEY*4 + 40).contains(localPosition)) {

        for (int i = 0; i < 10; ++i) {
          if (_buttons[i].getGlobalBounds().contains(localPosition)) {
            if (Input::isClicked) {
              _buttons[i].setFillColor(LIGHTGRAY);
              _buttons[i].setOutlineColor(GRAY);
            }
            else {
              if (i == 9) {
                _passwd.setString("");
              }
              else {
                std::string s = _passwd.getString();
                s += std::to_string(i+1);
                _passwd.setString(s);
              }
            }
          }
        }
      }
    }
  }


private:
  sf::Text _passwd;
  sf::Text _numbers[10];
  sf::RectangleShape _buttons[10];

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(getPosition()-getOrigin());
    states.transform.scale(getScale(), getOrigin());
    for (const auto& b : _buttons) {
      target.draw(b, states);
    }
    for (const auto& t : _numbers) {
      target.draw(t, states);
    }
    target.draw(_passwd, states);

  }

};

#endif
