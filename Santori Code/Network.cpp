#include "Network.h"
#include <thread>
#include "messenger.h"
Network::Network()
{
}

Network::~Network()
{
}

void Network::start()
{
	
}

void Network::recieve(sf::UdpSocket &socket, std::string IP, sf::TcpSocket &tcpSocket)
{
	sf::Packet packet;
	sf::IpAddress address;
	unsigned short remote_port;
	sf::Uint16 port;


	if (socket.receive(packet, address, remote_port) != sf::Socket::Done)
		std::cerr << "error reciving port";
	else
		if (packet >> port)

	remote_port = port;
	std::cout << "remote port: " << remote_port << std::endl;
	std::cout << "port :" << port << std::endl;
	

	if (tcpSocket.connect(IP, remote_port) != sf::Socket::Done)
		std::cerr << "error connecting to tcp socket: Port used : " << remote_port << "ip used :" << IP << std::endl;
	else {
		std::cout << "succesfully connected to Sever Socket" << remote_port << std::endl;
		std::cout  << std::endl;
		std::cout << "Waiting for game to start" << std::endl;

		while (StartGame == false) {
			msg = RecieveData(tcpSocket);
			Rec = msg;
			std::cout << "starting game" << std::endl;

			if (Rec = 6)
				StartGame = true;
		}
		connected = true;
		return;
	}
		
}

void Network::Connect(sf::TcpSocket &tcpSocket)
{
	
	while (connected == false) {
		std::string IP;
		sf::UdpSocket socket;
		sf::IpAddress address;
		sf::Packet packet;
		std::string user;

		unsigned short remote_port;
		remote_port = 2000;

		std::cout << "Please input the server IP: ";
		std::cin >> IP;
		std::cout << std::endl << "please input your username: ";
		std::cin >> user;

		address = IP;
		if (packet << user)
			if (socket.send(packet, IP, remote_port) != sf::Socket::Done)
				std::cerr << "failed to connected try again" << std::endl << std::endl;
			else {
				std::cout << "connection succesful" << std::endl;
				recieve(socket,IP,tcpSocket);
			}
		
	}
	

}
