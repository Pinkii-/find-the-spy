#ifndef RIPERINOSCREEN_H
#define RIPERINOSCREEN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"

class RiperinoScreen {

private:
    
public:
    RiperinoScreen() {}
     
    ~RiperinoScreen(){}
    
    void run(sf::RenderWindow* window, int player){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(Resources::OKButton);

        sf::Sprite avatar;
        avatar.setTexture(Resources::PlayerTextures[Resources::PlayerIndex[player]]);
            
        sf::Sprite bg;
        bg.setTexture(Resources::Riperino);
        
        while(open){
            
            dt = deltaClock.restart().asSeconds();
            
            time += dt;
             
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    return;
                    break;
                default:
                    break;
                }
            }
            
            
            s.scale(window->getSize().x/s.getGlobalBounds().width, window->getSize().x/s.getGlobalBounds().width);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, window->getSize().y - s.getGlobalBounds().height/2);
            
            bg.scale(window->getSize().x/bg.getGlobalBounds().width, window->getSize().x/bg.getGlobalBounds().width);
            bg.setPosition(window->getSize().x/2 - bg.getGlobalBounds().width/2, window->getSize().y/2 - bg.getGlobalBounds().height/2);
            
            avatar.scale(window->getSize().x/avatar.getGlobalBounds().width, window->getSize().x/avatar.getGlobalBounds().width);
            avatar.setPosition(window->getSize().x/2 - avatar.getGlobalBounds().width/2, window->getSize().y/2 - avatar.getGlobalBounds().height/2);
            
            
            Input::update(*window);
            
            if(Input::isClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    s.setTexture(Resources::PressedOKButton);
            }
            else {
                s.setTexture(Resources::OKButton);    
            }
            
            if(!Input::isClicked && Input::wasClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                return;
            }
            
            window->clear();  
            window->draw(s);
            window->draw(bg);
            window->draw(avatar);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE