#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include <mutex>
class NetworkManager
{


public:
	NetworkManager();
	~NetworkManager();

	//used for sending and reciveing data
	sf::Uint8 nothing = 200;
	sf::Uint8 sendback;
	sf::Packet Send;
	sf::Packet Recieved;

	//universal IDs for data
	const sf::Uint8  turn = 1;
	const sf::Uint8  pos = 2;
	const sf::Uint8  playerID = 3;
	const sf::Uint8  vic = 4;
	const sf::Uint8  build = 5;
	const sf::Uint8  Play = 6;
	const sf::Uint8  fourPlayer = 7;

	
	//used in child classes
	sf::Uint8 msg;
	int display;
	sf::Uint8 sending;
	int Rec;
	bool StartGame = false;
	

	void SendDataType(sf::TcpSocket& Socket, sf::Uint8 type);
	void SendData(sf::TcpSocket& Socket, sf::Uint8 data);
	sf::Uint8 RecieveData(sf::TcpSocket& Socket);
};

