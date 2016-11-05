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
    
    void run(sf::RenderWindow* window, int player, Resources& res){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(res.OKButton);

        sf::Sprite avatar;
        avatar.setTexture(res.PlayerTextures[res.PlayerIndex[player]]);
        
        sf::Sprite icon;
        int sign = 1;
        int restInPeace = -1;
        if(rand()%2 == 0) {
            sign = -1;
            restInPeace = 1;
        }
        int step = 1;
        if(res.PlayerRol[res.PlayerIndex[player]] == 1){
            icon.setTexture(res.Spy);
        }
        else {
            while(step < res.PlayerIndex.size()){
//                int nextIndex = sign? player+step*sign%res.PlayerIndex.size(): res.PlayerIndex().size - player+step*sign;
                int n = res.PlayerIndex.size();
                int i = player+step*sign;
                int nextIndex = (i % n + n) % n;
                if(res.PlayerRol[res.PlayerIndex[nextIndex]] == 1){
                    step = res.PlayerIndex.size()+1;
                    if(sign > 0) icon.setTexture(res.RightArrow);
                    else icon.setTexture(res.LeftArrow);
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
            
            
            s.scale(window->getSize().x/4/s.getGlobalBounds().width, window->getSize().x/4/s.getGlobalBounds().width);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, window->getSize().y - s.getGlobalBounds().height);
            
            icon.scale(window->getSize().x/4/icon.getGlobalBounds().width, window->getSize().x/4/icon.getGlobalBounds().width);
            icon.setPosition(window->getSize().x/2 - icon.getGlobalBounds().width/2, window->getSize().y/2 - icon.getGlobalBounds().height/2);
            
            avatar.scale(window->getSize().x/3/avatar.getGlobalBounds().width, window->getSize().x/3/avatar.getGlobalBounds().width);
            avatar.setPosition(window->getSize().x/2 - avatar.getGlobalBounds().width/2, 0);
            
            
            Input::update(*window);
            
            if(Input::isClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    s.setTexture(res.PressedOKButton);
            }
            else {
                s.setTexture(res.OKButton);    
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