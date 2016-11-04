#include "Resources.hpp"
#include <iostream>
#define TEXTUREPATH "res/pics"
// sf::Texture        Resources::....
sf::Font Resources::font;
sf::Texture Resources::OKButton;
sf::Texture Resources::PressedOKButton;

void Resources::load() {
    //...loadFromFile();
    if (!font.loadFromFile("res/fonts/font.otf")) std::cout << "penefont" << std::endl;

    if(! OKButton.loadFromFile (TEXTUREPATH+std::string("buttons/OKButton.png")) ) std::cout << "okbutton not loaded" << std::endl;
    if(! PressedOKButton.loadFromFile (TEXTUREPATH+std::string("buttons/PressedOKButton.png")) ) std::cout << "pressedokbutton not loaded" << std::endl;
}
