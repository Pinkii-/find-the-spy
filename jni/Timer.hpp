#ifndef TIMER_H
#define TIMER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"

class Timer {

private:
    sf::Text t;

    int min;
    int sec;
    
public:
    Timer() {
        min = 3;
        sec = 1;
    }
     
    ~Timer(){}
    
    std::string myToString(int i){
        if(i <= 9) return "0"+std::to_string(i);
        else return std::to_string(i);
    }
    void run(sf::RenderWindow* window, int tim, Resources& res){
        
        float time = tim;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        t.setFont(res.font);
        
        sf::Sprite s;
        s.setTexture(res.OKButton);
        
        while(open){
            
            dt = deltaClock.restart().asSeconds();
            
            time -= dt;
            min = time/60;
            sec = time-(min*60);
            
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
            
            t.setString(myToString(min)+":"+myToString(sec));

            t.scale(window->getSize().x/t.getGlobalBounds().width/2, window->getSize().x/t.getGlobalBounds()/2.width);
            t.setPosition(window->getSize().x/2 - t.getGlobalBounds().width/2, window->getSize().y/2 - t.getGlobalBounds().height/2);
            
            s.scale(window->getSize().x/4/s.getGlobalBounds().width, window->getSize().x/4/s.getGlobalBounds().width);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, window->getSize().y - s.getGlobalBounds().height);
            
            Input::update(*window);
            
            if(Input::isClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    s.setTexture(res.PressedOKButton);
            }
            
            if(!Input::isClicked && Input::wasClicked && s.getGlobalBounds().contains(sf::Vector2f(Input::pos.x,Input::pos.y))){
                    return;
            }
            
            window->clear();
            window->draw(t);            
            window->draw(s);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE