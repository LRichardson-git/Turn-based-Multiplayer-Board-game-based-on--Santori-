#pragma once
#include <string>
#include "NetworkManager.h"
class Reciever : public NetworkManager
{
	
public:
	void receive(sf::TcpSocket& CSocket, sf::TcpSocket& RSocket, sf::TcpSocket& BSocket, sf::TcpSocket& DSocket, unsigned short sPlayers, unsigned short nPlayer);

	

	
};

