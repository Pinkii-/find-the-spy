#ifndef TIMER_H
#define TIMER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    void run(sf::RenderWindow* window, int tim){
        
        int time = tim;
        
        open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        t.setFont(Resources::font);
        
        sf::Sprite s;
        s.setTexture(Resources::OKButton);
        
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
            
            t.setText(myToString(min)+":"+myToString(sec));

            t.scale(window->getSize().x/t.getGlobalBounds().width, window->getSize().x/t.getGlobalBounds().width);
            t.setPosition(window->getSize().x/2 - t.getGlobalBounds().width/2, window->getSize().y/2 - t.getGlobalBounds().height/2);
            
            Input::update(*window);
            
            if(Input::isClick && s.getGlobalBounds().contains(Input::pos)){
                    s.setTexture(Resources::clickedOKButton);
            }
            
            if(!Input::isClick && Input::wasClicked && s.getGlobalBounds().contains(Input::pos)){
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