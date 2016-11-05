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
        double cosinus(double x,double prec = 0.001)
{
    double t , s ;
    int p;
    p = 0;
    s = 1.0;
    t = 1.0;
    while(fabs(t/s) > prec)
    {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
    }
    return s;}
    
    float sinus(float x)
{
  float res=0, pow=x, fact=1;
  for(int i=0; i<5; ++i)
  {
    res+=pow/fact;
    pow*=x*x;
    fact*=(2*(i+1))*(2*(i+1)+1);
  }

  return res;
}

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
        
        float angle = 360/players.size();
        
        for(size_t i = 0; i < players.size(); ++i){
            float concreteAngle = angle*i;
            players[i].setScale(
                (window->getSize().x/5)/players[i].getGlobalBounds().width, 
                (window->getSize().x/5)/players[i].getGlobalBounds().width);
            
            players[i].setPosition(
                window->getSize().x/2 + cosinus(concreteAngle*0.0174532925, 0.001)*radi, 
                window->getSize().y/2 + sinus(concreteAngle*0.0174532925)*radi);
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