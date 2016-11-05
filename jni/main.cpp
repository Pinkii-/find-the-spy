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
#include "RiperinoScreen.hpp"
#include "SignInScreen.hpp"
#include "AutenticateScreen.hpp"
#include "InitialScreen.hpp"
#include "Calculator.hpp"

int main(int argc, const char* argv[]){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "NoCalPlorar");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true); 
    srand (time(NULL));

    Resources resources;
    resources.load();
    
    Calculator calc(resources);
    calc.setPosition(window.getSize().x/2, 100);
    calc.setOrigin(SIZEX*1.5, 0);

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

        int playerAmount;// = resources.PlayerIndex.size();
        InitialScreen initialScreen;
        playerAmount = initialScreen.run(&window, 2, resources);
        for(int i = 0; i < playerAmount; ++i){
            resources.PlayerIndex.push_back(i);
            resources.PlayerRol.push_back(0);
        }
        
        int spyAmount = playerAmount/2.5;
        
        while(spyAmount > 0){
            int candidate = rand()%playerAmount;
            if(resources.PlayerRol[resources.PlayerIndex[candidate]] != 1){
                resources.PlayerRol[resources.PlayerIndex[candidate]] = 1;
                --spyAmount;
            }
        }
        
         SignInScreen signInScreen;
         for(int i = 0; i < playerAmount; ++i){
             signInScreen.initializePlayer(window, i, resources);
         }

        AutenticateScreen autenticateScreen;

        DecissionScreen decissionScreen;

        Timer timerScreen;
        KillingSpree killingSpreeScreen;

        RiperinoScreen riperinoScreen;

        ReshuffleScreen reshuffleScreen;

        bool playing = true;

        while(playing){

            for(int i = 0; i < playerAmount; ++i){
                autenticateScreen.run(&window, i, resources);
                decissionScreen.run(&window, i, resources);
            }

            timerScreen.run(&window, 3*60, resources);

            std::vector<int> kills(playerAmount,0);
            for(int i = 0; i < playerAmount; ++i){
                autenticateScreen.run(&window, i, resources);
                int victim = killingSpreeScreen.run(&window, i, resources);
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

            riperinoScreen.run(&window,mostVoted, resources);

            resources.PlayerIndex.erase(resources.PlayerIndex.begin() + mostVoted);
            --playerAmount;

            reshuffleScreen.run(&window, resources);
        }
    }
}
