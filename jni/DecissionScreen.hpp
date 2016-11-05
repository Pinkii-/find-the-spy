#ifndef DECISSIONSCREEN_H
#define DECISSIONSCREEN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"

class DecissionScreen {

private:
    
public:
    DecissionScreen() {}
     
    ~DecissionScreen(){}
    
    void run(sf::RenderWindow* window, int player){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(Resources::OKButton);

        sf::Sprite avatar;
        avatar.setTexture(Resources::PlayerTextures[Resources::PlayerIndex[player]]);
        
        sf::Sprite icon;
        int sign = 1;
        int restInPeace = -1;
        if(rand()%2 == 0) {
            sign = -1;
            restInPeace = 1;
        }
        int step = 1;
        if(Resources::PlayerRol[Resources::PlayerIndex[player]] == 1){
            icon.setTexture(Resources::Spy);
        }
        else {
            while(step < Resources::PlayerIndex.size()){
//                int nextIndex = sign? player+step*sign%Resources::PlayerIndex.size(): Resources::PlayerIndex().size - player+step*sign;
                int n = Resources::PlayerIndex.size();
                int i = player+step*sign;
                int nextIndex = (i % n + n) % n;
                if(Resources::PlayerRol[Resources::PlayerIndex[nextIndex]] == 1){
                    step = Resources::PlayerIndex.size()+1;
                    if(sign > 0) icon.setTexture(Resources::RightArrow);
                    else icon.setTexture(Resources::LeftArrow);
                }
                
                restInPeace *= sign;
                if(restInPeace > 0) ++step;
                sign *= -1;
            }
        }
            
        
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
            
            icon.scale(window->getSize().x/icon.getGlobalBounds().width, window->getSize().x/icon.getGlobalBounds().width);
            icon.setPosition(window->getSize().x/2 - icon.getGlobalBounds().width/2, window->getSize().y/2 - icon.getGlobalBounds().height/2);
            
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
            window->draw(icon);
            window->draw(avatar);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE