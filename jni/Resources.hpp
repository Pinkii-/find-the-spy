#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#define TEXTUREPATH "res/pics/"

class Resources {
public:
    
    
sf::Font font;

sf::Texture OKButton;
sf::Texture PressedOKButton;

sf::Texture Button;
sf::Texture ButtonPress;
    
sf::Texture Riperino;
    
sf::Texture LeftArrow;
sf::Texture RightArrow;
    
sf::Texture Spy;
    
std::vector<int> PlayerRol;
std::vector<int> PlayerIndex;
std::vector<sf::Texture> PlayerTextures;

      
        void load(){
            //...loadFromFile();
            if (!font.loadFromFile("res/fonts/font.otf")) std::cout << "penefont" << std::endl;

            if(! OKButton.loadFromFile (TEXTUREPATH+std::string("buttons/OKButton.png")) ) std::cout << "okbutton not loaded" << std::endl;
            if(! PressedOKButton.loadFromFile (TEXTUREPATH+std::string("buttons/PressedOKButton.png")) ) std::cout << "pressedokbutton not loaded" << std::endl;

            if(! Button.loadFromFile (TEXTUREPATH+std::string("buttons/Button.png")) ) std::cout << "startbuton not loaded" << std::endl;
            if(! ButtonPress.loadFromFile (TEXTUREPATH+std::string("buttons/ButtonPress.png")) ) std::cout << "startbuttonpress not loaded" << std::endl;

            if(! Riperino.loadFromFile (TEXTUREPATH+std::string("riperino.png")) ) std::cout << "riperino not loaded" << std::endl;

            if(! LeftArrow.loadFromFile (TEXTUREPATH+std::string("arrowleft.png")) ) std::cout << "arrowleft not loaded" << std::endl;
            if(! RightArrow.loadFromFile (TEXTUREPATH+std::string("arrowright.png")) ) std::cout << "arrowright not loaded" << std::endl;

            if(! Spy.loadFromFile (TEXTUREPATH+std::string("spy.png")) ) std::cout << "spy not loaded" << std::endl;
            
            PlayerTextures.push_back(Spy);
            PlayerTextures.push_back(Riperino);
            PlayerTextures.push_back(Button);
            
            PlayerIndex.push_back(0);
            PlayerIndex.push_back(1);
            PlayerIndex.push_back(2);
            
            PlayerRol.push_back(0);
            PlayerRol.push_back(1);
            PlayerRol.push_back(2);
        }
    
    //  sf::Texture ...
private:

};

#endif
