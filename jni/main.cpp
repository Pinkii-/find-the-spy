//GRAVITY
#include <time.h>       /* time */
#include <string>       /*strings*/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, const char* argv[]){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Yuegal");
    srand (time(NULL));

    sf::Clock clock;
    while (window.isOpen()) {
      float deltaTime = clock.restart().asSeconds();

      sf::Event event;
      while (window.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            exit(0);
            break;
        }
      }
    }
}
