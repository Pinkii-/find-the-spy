#ifndef KILLINGSPREE_H
#define KILLINGSPREE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "Input.hpp"

class KillingSpree {

private:
    
public:
    KillingSpree() {
        
    }
     
    ~KillingSpree(){}
    
    std::string myToString(int i){
        if(i <= 9) return "0"+std::to_string(i);
        else return std::to_string(i);
    }
    
    int run(sf::RenderWindow* window, int tim){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(Resources::OKButton);
        
        std::vector<sf::Sprite> players;
        for(size_t i = 0; i < players.size(); ++i){
            players[i].setTexture(Resources::PlayerTextures[i]);
        }
        
        sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
        float radi = window->getSize().x/4;
        
        float angle = 360/players.size();
        
        for(size_t i = 0; i < players.size(); ++i){
            float concreteAngle = angle*i;
            players[i].setScale((window->getSize().x/4)/players[i].getGlobalBounds().width, (window->getSize().x/4)/players[i].getGlobalBounds().width);
            players[i].setPosition(window->getSize().x/2 + std::cos(concreteAngle)*radi, window->getSize().y/2 + std::sin(concreteAngle)*radi);
        }
        
        
        while(open){
            
            dt = deltaClock.restart().asSeconds();
            
            time += dt;
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    return -1;
                    break;
                default:
                    break;
                }
            }
            
            Input::update(*window);            
            
            for(size_t i = 0; i < players.size(); ++i){
                if(Input::isClicked && players[i].getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    players[i].setRotation(12);
                }
                else {
                    players[i].setRotation(0);
                }
                if(!Input::isClicked && Input::wasClicked && players[i].getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    return i;
                }   
            }
            
/*            if(Input::isClicked && s.getGlobalBounds().contains(Input::pos)){
                    s.setTexture(Resources::clickedOKButton);
            }
            if(!Input::isClicked && Input::wasClicked && s.getGlobalBounds().contains(Input::pos)){
                return -1;
            }*/
            if(time >= 220) return -1;
            
            window->clear();
            for(size_t i = 0; i < players.size(); ++i){
                window->draw(players[i]);
            }
            window->draw(s);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE