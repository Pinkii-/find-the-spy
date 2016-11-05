#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Resources {
public:
    static void load();
    static sf::Font font;

    static sf::Texture OKButton;
    static sf::Texture PressedOKButton;

    static sf::Texture Button;
    static sf::Texture ButtonPress;
    
    static sf::Texture Riperino;
    
    static sf::Texture LeftArrow;
    static sf::Texture RightArrow;
    
    static sf::Texture Spy;
    
    static std::vector<sf::Texture> PlayerTextures;
    //static sf::Texture ...
private:

};

#endif
