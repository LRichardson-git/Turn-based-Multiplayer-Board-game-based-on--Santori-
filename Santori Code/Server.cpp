#include "Server.h"
#include <SFML/Graphics.hpp>



void Server::runserver()
{
    bool setup = true;
        //Server Lobby setup
    while (setup == true) {

    
    std::cout << "Server Setup \n";
    std::cout << "How many Players will be in your game? : 2 or 4? \n";
    
    std::cin >> Input;
    std::cout << std::endl;
    if (Input == "2") {
        maxPlayers = 2;
        std::cout << "you have choosen 2 players \n";
        setup = false;
    }

    else if (Input == "4") {
        maxPlayers = 4;
        std::cout << "you have choosen 4 players \n";
        setup = false;

    }
    else
        std::cout << "please choose a approratite amount of players \n";
    }

    std::cout << "Creating Server \n";
    std::cout << std::endl;
    std::cout << std::endl;

        //Server Creation

    sf::UdpSocket usocket;
    if (usocket.bind(2000) != sf::Socket::Done) {
        std::cerr << "error binding to udp port \n";
    }
    bool serverUp = true;
    
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    std::cout << "UDP bound to port: " << usocket.getLocalPort() << std::endl;
    std::cout << "Local ip:" << ip << std::endl;


        //Create thread to detect connections
    std::thread UdpIPConnect([&usocket] {
        std::string recieved;
        sf::Packet packet;
        sf::IpAddress address;
        unsigned short remote_port;
        sf::Uint16 myPort = 2000;
        packet.clear();

        while (true) {

            if (usocket.receive(packet, address, remote_port) != sf::Socket::Done)
                std::cout << "error recieving connection" << std::endl;

            else {
                if (packet >> recieved) {
                    std::cerr << "User " << recieved << " just connected "  << std::endl;
                    //send back msg of ip address
                    packet.clear();
                    myPort++;
                    if (packet << myPort) {
                        usocket.send(packet, address, remote_port);
                    }
                        


                }

            }
            

        }
    });
    UdpIPConnect.detach();
     
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Waiting for Players to connect" << std::endl;
    std::cout << std::endl;


    //Create threads for detecting Playersing joining
    //Reasion I have multiple functions is because couldn't get threads to work properly on one function that accepts the parameters :( 
    std::thread first(&Server::PlayerOne, this);
    first.detach();
    std::thread second(&Server::PlayerTwo, this);
    second.detach();

    if (maxPlayers == 4) {
        std::thread Third(&Server::Playerthree, this);
        Third.detach();
        std::thread Fourth(&Server::PlayerFour, this);
        Fourth.detach();

    }
  
        
   
        
    Input.clear();
    while (serverUp == true) {

        if (players == maxPlayers && StartGame == false) {
            std::cout << "All players are connected Press eneter Q to start the game"<< std::endl;
            std::cin >> Input;
            if (Input == "Q" || Input == "q") {
                SendData(tsocket, Play);
                SendData(tsocket2, Play);
                if (maxPlayers == 4) {
                    SendData(tsocket3, Play);
                    SendData(tsocket4, Play);
                }
               //stargame = true
            }
            else {
                std::cout << "you need all Players connected to start the game" << std::endl;
            }
            //maybe some commands here
        }
    }
        
}


void Server::PlayerOne() {
    sf::TcpListener listener;
    unsigned int local_port = 2001;

    if (listener.listen(local_port) != sf::Socket::Done) {
        std::cerr << "TCP BINDING ERROR" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "tcp socket bound to port: " << listener.getLocalPort() << std::endl;


    if (listener.accept(tsocket) != sf::Socket::Done) {
        std::cerr << "accepting problems on port: " << local_port << std::endl;
    }

    else {
        std::cerr << "bound to socket: " << local_port << std::endl;

        players++;
       

    }

    while (true) {


        r.receive(tsocket, tsocket2, tsocket3 ,tsocket4, maxPlayers,player1);

    }


}


void Server::PlayerTwo() {

    sf::TcpListener listener;
    unsigned int local_port = 2002;
    
    if (listener.listen(local_port) != sf::Socket::Done) {
        std::cerr << "TCP BINDING ERROR" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "tcp socket bound to port: " << listener.getLocalPort() << std::endl;

    
    if (listener.accept(tsocket2) != sf::Socket::Done) {
        std::cerr << "accepting problems on port: " <<  local_port << std::endl;
    }

    else {
        std::cerr << "bound to socket: " << local_port << std::endl;

        players++;
      

    }

    while (true) {


        r.receive(tsocket2, tsocket, tsocket4, tsocket3, maxPlayers,player2);

    }

}



void Server::Playerthree() {

    sf::TcpListener listener;
    unsigned int local_port = 2003;

    if (listener.listen(local_port) != sf::Socket::Done) {
        std::cerr << "TCP BINDING ERROR" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "tcp socket bound to port: " << listener.getLocalPort() << std::endl;


    if (listener.accept(tsocket3) != sf::Socket::Done) {
        std::cerr << "accepting problems on port: " << local_port << std::endl;
    }

    else {
        std::cerr << "bound to socket: " << local_port << std::endl;

        players++;
        

    }

    while (true) {


        r.receive(tsocket3, tsocket2, tsocket, tsocket4, maxPlayers,player3);

    }

}

void Server::PlayerFour() {

    sf::TcpListener listener;
    unsigned int local_port = 2004;

    if (listener.listen(local_port) != sf::Socket::Done) {
        std::cerr << "TCP BINDING ERROR" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "tcp socket bound to port: " << listener.getLocalPort() << std::endl;


    if (listener.accept(tsocket4) != sf::Socket::Done) {
        std::cerr << "accepting problems on port: " << local_port << std::endl;
    }

    else {
        std::cerr << "bound to socket: " << local_port << std::endl;

        players++;
       

    }
    while (true) {


        r.receive(tsocket4, tsocket, tsocket2, tsocket3, maxPlayers,player4);

    }
}