//GRAVITY
#include <time.h>       /* time */
#include <string>       /*strings*/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "KillingSpree.hpp"
#include "Timer.hpp"
#include "ReshufleScreen.hpp"
#include "DecissionScreen.hpp"

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

        int playerAmount = 0;
        //InitialScreen initialScreen;
        //playerAmount = initialScreen.run();
    
//         SignInScreen signInScreen;
//         for(int i = 0; i < playerAmount; ++i){
//             signInScreen.initializePlayer(i);
//         }
        
//         AutenticateScreen autenticateScreen;
        
        DecissionScreen decissionScreen;

        Timer timerScreen;
        KillingSpree killingSpreeScreen;
        
//         DeathScreen deathScreen;

        ReshuffleScreen reshuffleScreen;
        
        bool playing = true;
        
        while(playing){
            
            for(int i = 0; i < playerAmount; ++i){
//                 autenticateScreen.autenticate(i);
                decissionScreen.run(&window, i);
            }
            
            timerScreen.run(&window, 3*60);
            
            std::vector<int> kills(playerAmount,0);
            for(int i = 0; i < playerAmount; ++i){
//                 autenticateScreen.autenticate(i);
                int victim = killingSpreeScreen.run(&window, i);
                if(victim >= 0) ++kills[victim];
            }
            
            int mostVoted = 0;
            int maxVotes = 0;
            for(int i = 0; i < playerAmount; ++i){
                if(kills[i] > maxVotes) {
                    mostVoted = i;
                    maxVotes = kills[i];
                }
                //TODO: BE FAIR
                if(kills[i] == maxVotes && rand()%2 == 0){
                    mostVoted = i;                
                    maxVotes = kills[i];
                }
            }            
            
//             deathScreen.show(mostVoted);
            
              Resources::PlayerIndex.erase(Resources::PlayerIndex.begin() + mostVoted);
              --playerAmount;
              
              reshuffleScreen.run(&window);
        }
    }
}
