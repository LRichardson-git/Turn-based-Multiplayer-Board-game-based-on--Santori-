#include "game.hpp"
#include <iostream>
#include "messenger.h"
#include <thread>
game::game():
    window(sf::VideoMode(600, 600), "Santorini")
{
    w = new world(window, this);
}

game::~game()
{
    delete w;
}

void game::play(sf::TcpSocket& tcpSocket)
{
   // if (update == true)
    w->update(tcpSocket);

    w->draw();
    
    
 

}

void game::victory()
{
    
        
        std::cout << "YOU HAVE WON THE GAME" << std::endl;
        std::cout << "if you wish to play again close and reopon the program" << std::endl;
        std::cout << std::endl;
        std::cout << " press escape to close the program";
        
        system("pause");
       
    
    
   
}

void game::defeat()
{
    
     
         std::cout << "YOU HAVE LOST THE GAME" << std::endl;
         std::cout << "if you wish to play again close and reopon the program" << std::endl;
         std::cout << std::endl;
         std::cout << " press escape to close the program";
        
        system("pause");



    }
    


void game::run(sf::TcpSocket &tcpSocket)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
           // else if (event.type == sf::Event::GainedFocus)
             //   update = true;
            //else if (event.type == sf::Event::LostFocus)
               // update = false;
        }
        window.clear();
        switch (state) {
            case gamestate::play:
                play(tcpSocket);
                break;
            case gamestate::victory:
                victory();
                break;
            case gamestate::defeat:
                defeat();
                break;
            case gamestate::terminate:
                return;
            default:
                break;       
        }
        window.display();
    }
}
