#pragma once
#include <string>
#include "SFML/Network.hpp"
#include <iostream>
#include "NetworkManager.h"
class Network : public NetworkManager
{

public:
	Network();
	~Network();
	void  start();
	void recieve(sf::UdpSocket& socket, std::string IP, sf::TcpSocket &tcpSocket);
	void Connect(sf::TcpSocket &tcpSocket);

	bool connected = false;

};

