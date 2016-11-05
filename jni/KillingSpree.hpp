#ifndef KILLINGSPREE_H
#define KILLINGSPREE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "Input.hpp"
#include <math.h>
      
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
  

  float mcos(float x){
    if( x < 0.0f ) 
        x = -x;
    while( 3.1415926535 < x )
        x -= 0.636619772367;
    return 1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - x*x/56.0f )));
    }
 
float msin(float x){return cos(x-1.570796326794);}


    int run(sf::RenderWindow* window, int tim, Resources& res){
        
        int time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        std::vector<sf::Sprite> players(res.PlayerIndex.size());
        for(size_t i = 0; i < players.size(); ++i){
            players[i].setTexture(res.PlayerTextures[res.PlayerIndex[i]]);
            players[i].setOrigin(players[i].getLocalBounds().width/2,
                                 players[i].getLocalBounds().height/2);
        }
        sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
        float radi = window->getSize().x/4;
        
        float angle = -360/float(players.size());
        
            //std::cout << "le pos" << std::endl;
        for(size_t i = 0; i < players.size(); ++i){
            float concreteAngle = (int(angle*i) +360 )%360;
            players[i].setScale(
                (window->getSize().x/5)/players[i].getGlobalBounds().width, 
                (window->getSize().x/5)/players[i].getGlobalBounds().width);
            
            players[i].setPosition(
                window->getSize().x/2 + mcos(concreteAngle*0.0174532925)*radi, 
                window->getSize().y/2 - msin(concreteAngle*0.0174532925)*radi);
                //std::cout << players[i].getPosition().x << " , " << players[i].getPosition().y << std::endl;
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
            
            if(time >= 220) return -1;
            
            window->clear();
            for(size_t i = 0; i < players.size(); ++i){
                window->draw(players[i]);
            }

            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE