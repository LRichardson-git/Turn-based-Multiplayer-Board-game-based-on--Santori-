#pragma once
#define PORT 2001
#include <SFML/Network.hpp>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <conio.h>
#include "Reciever.h"
#include "NetworkManager.h"
class Server : public NetworkManager
{
	
	public:
		Reciever r;

		//functions for player data
		//had issues with threads so ended up like this
		void runserver();
		void PlayerOne();
		void PlayerTwo();
		void Playerthree();
		void PlayerFour();
		bool ready = false;

		
		//sockets for connections
		sf::TcpSocket tsocket;
		sf::TcpSocket tsocket2;
		sf::TcpSocket tsocket3;
		sf::TcpSocket tsocket4;
		
		//player info 
		std::string Input;
		unsigned short maxPlayers = 0;
		unsigned short players = 0;
		unsigned short player1 = 0;
		unsigned short player2 = 1;
		unsigned short player3 = 2;
		unsigned short player4 = 3;
		

};

