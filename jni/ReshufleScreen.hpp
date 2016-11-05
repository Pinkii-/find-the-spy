#ifndef RESHUFFLE_H
#define RESHUFFLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "Input.hpp"
#include<stdio.h>
#include<math.h>

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

    float mcos(float x){
    if( x < 0.0f ) 
        x = -x;
    while( 3.1415926535 < x )
        x -= 0.636619772367;
    return 1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - x*x/56.0f )));
    }
 
    float msin(float x){return cos(x-1.570796326794);}


    
    void run(sf::RenderWindow* window, Resources& res){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(res.OKButton);
        
        sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
        float radi = window->getSize().x/4;
        
        std::vector<sf::Sprite> oldPlayerPositions(res.PlayerIndex.size());
        for(size_t i = 0; i < oldPlayerPositions.size(); ++i){
            oldPlayerPositions[i].setTexture(res.PlayerTextures[res.PlayerIndex[i]]);
        }
        
        std::random_shuffle(res.PlayerIndex.begin(), res.PlayerIndex.end());
        std::vector<sf::Sprite> players(res.PlayerIndex.size());
        for(size_t i = 0; i < players.size(); ++i){
            players[i].setTexture(res.PlayerTextures[res.PlayerIndex[i]]);
        }
        
        float angle = 360/players.size();
        
        for(size_t i = 0; i < players.size(); ++i){
            float concreteAngle = angle*i;
            players[i].setScale(
                (window->getSize().x/5)/players[i].getGlobalBounds().width, 
                (window->getSize().x/5)/players[i].getGlobalBounds().width);
            
            players[i].setPosition(
                window->getSize().x/2 + mcos(concreteAngle*0.0174532925)*radi, 
                window->getSize().y/2 + msin(concreteAngle*0.0174532925)*radi);
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
            
            s.scale(window->getSize().x/6/s.getGlobalBounds().width, window->getSize().x/6/s.getGlobalBounds().width);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, window->getSize().y - s.getGlobalBounds().height);
            
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
            for(size_t i = 0; i < players.size(); ++i){
                window->draw(players[i]);
            }
            window->draw(s);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE