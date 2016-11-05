#ifndef __SIGNINSCREEN_HPP__
#define __SIGNINSCREEN_HPP__

#include "Drawer.hpp"
#include "Calculator.hpp"


class SignInScreen {
public:
  void initializePlayer(sf::RenderWindow& window, int index) {
    float offset = 40;

    Drawer drawer(_colors[index]);
    drawer.setPosition(window.getSize().x/2, offset);
    drawer.setOrigin(100, 0);

    Calculator calc;
    calc.setPosition(window.getSize().x/2, FRAMESIZEY + offset*2.5);
    calc.setOrigin(SIZEX*1.5, 0);

    bool open = true;

    sf::Clock clock;
    while(open) {
      float deltaTime = clock.restart().asSeconds();

      sf::Event event;
      while (window.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
          window.close();
          exit(0);
          break;
          default:
          break;
        }
      }

      Input::update(window);
      calc.update(deltaTime);
      drawer.update(deltaTime);

      window.clear(sf::Color::Black);

      window.draw(drawer);
      window.draw(calc);

      window.display();
    }

  }
private:
  sf::Color _colors[4] = {sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta};
};

#endif
