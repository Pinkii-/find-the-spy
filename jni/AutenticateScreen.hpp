#ifndef AUTENTICATE_H
#define AUTENTICATE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Resources.hpp"

class AutenticateScreen {

private:
    
public:
    AutenticateScreen() {}
     
    ~AutenticateScreen(){}
    
    void run(sf::RenderWindow* window, int player, Resources& res){
        
        float time = 0;
        
        bool open = true;
        
        float dt = 0;
        sf::Clock deltaClock;
        
        sf::Sprite s;
        s.setTexture(res.OKButton);

        sf::Sprite avatar;
        avatar.setTexture(res.PlayerTextures[res.PlayerIndex[player]]);
        
        
        Calculator calc(res);
        calc.setPosition(window->getSize().x/2, window->getSize().y/2 - 80);
        calc.setOrigin(SIZEX*1.5, 0);    
        
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
            
            calc.update(dt);
            
            s.scale(window->getSize().x/8/s.getGlobalBounds().width, window->getSize().x/8/s.getGlobalBounds().width);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, window->getSize().y - s.getGlobalBounds().height);
             
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
                if(calc._passwd.getString() == res.Passwords[res.PlayerIndex[player]]) return;
                //else std::cout << std::string(calc._passwd.getString()) << " vs " << res.Passwords[res.PlayerIndex[player]] << std::endl;
            }
            
            if(time > 100) return;
            
            window->clear();  
            window->draw(s);
            window->draw(calc);
            window->draw(avatar);
            window->display();
             
        }
        
    }

};

#endif // GRAVITY OR SOMETHING MUEJEJEJEE