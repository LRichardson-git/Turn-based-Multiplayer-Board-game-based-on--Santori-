#include "game.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include "Server.h"
#include "Network.h"

int main()
{
    
    std::string choice;

    //Welcome message
    std::cout << "Welcome to santori" << std::endl;
    std::cout << "TO Create a server press S" << std::endl;
    std::cout << "To Join a Server press T" << std::endl;

    std::cin >> choice;

    if (choice == "s" || choice == "S") {
        Server server;
        server.runserver();
    }


    else if (choice == "t" || choice == "T") {
        sf::TcpSocket tcpSocket;
        Network network;
        network.Connect(tcpSocket);

        if (network.StartGame == true) {
            game g;
            g.run(tcpSocket);
            return 0;
        }
    }

    
}