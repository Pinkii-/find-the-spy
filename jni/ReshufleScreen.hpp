#ifndef RESHUFFLE_H
#define RESHUFFLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "Input.hpp"

class ReshuffleScreen {

private:
    
public:
    ReshuffleScreen() {
        
    }
     
    ~ReshuffleScreen(){}
    
    std::string myToString(int i){
        if(i <= 9) return "0"+std::to_string(i);
        else return std::to_string(i);
    }
    
    void run(sf::RenderWindow* window){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(Resources::OKButton);
        
        sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
        float radi = window->getSize().x/4;
        
        std::vector<sf::Sprite> oldPlayerPositions(Resources::PlayerTextures.size());
        for(size_t i = 0; i < oldPlayerPositions.size(); ++i){
            oldPlayerPositions[i].setTexture(Resources::PlayerTextures[i]);
        }
        
        std::random_shuffle(Resources::PlayerTextures.begin(), Resources::PlayerTextures.end());
        std::vector<sf::Sprite> players(Resources::PlayerTextures.size());
        for(size_t i = 0; i < players.size(); ++i){
            players[i].setTexture(Resources::PlayerTextures[i]);
        }
        
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
                    return;
                    break;
                default:
                    break;
                }
            }
            
            Input::update(*window);            
            
            if(Input::isClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                s.setTexture(Resources::PressedOKButton);
            }
            if(!Input::isClicked && Input::wasClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                return;
            }   
            
            if(time >= 1200) return;
            
            window->clear();
            window->draw(s);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE