#ifndef __SIGNINSCREEN_HPP__
#define __SIGNINSCREEN_HPP__

#include "Drawer.hpp"
#include "Calculator.hpp"


class SignInScreen {
public:
  void initializePlayer(sf::RenderWindow& window, int index, Resources& res) {
    float offset = 40;

    sf::Sprite nextButton;
    nextButton.setTexture(res.OKButton);
    Drawer drawer(_colors[index]);
    drawer.setPosition(window.getSize().x/2, offset);
    drawer.setOrigin(100, 0);

    Calculator calc(res);
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
      
      nextButton.scale(window.getSize().x/8/nextButton.getGlobalBounds().width, window.getSize().x/8/nextButton.getGlobalBounds().width);
      nextButton.setPosition(window.getSize().x/2 - nextButton.getGlobalBounds().width/2, window.getSize().y - nextButton.getGlobalBounds().height);
      
        if(Input::isClicked && nextButton.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                nextButton.setTexture(res.PressedOKButton);
        }
        else {
            nextButton.setTexture(res.OKButton);    
        }
        if(!Input::isClicked && Input::wasClicked && nextButton.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
            if(calc._passwd.getString() != ""){
                res.PlayerTextures.push_back(drawer._texture);    
                res.Passwords.push_back(calc._passwd.getString());
                std::cout << std::string(calc._passwd.getString()) << std::endl;
                return;
            }
        }

      window.clear(sf::Color::Black);

      window.draw(drawer);
      window.draw(calc);
      window.draw(nextButton);
      window.display();
    }

  }
private:
  sf::Color _colors[4] = {sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta};
};

#endif
